clear
export PATH=/usr/local/i386elfgcc/bin:$PATH
rm -rf bin/
rm -rf a_debug/
mkdir bin/
mkdir a_debug/                              # a_debug just so it stays up on the folder listing(ocd: yes)

CC_FLAGS="-g -m32 -ffreestanding -fno-pic -c"

# bootloader
nasm -f bin "./bootloader/stage1/stage1_bootloader.asm" -o "./bin/stage1_bootloader.bin"
nasm -f bin "./bootloader/stage2/stage2_bootloader.asm" -o "./bin/stage2_bootloader.bin"
nasm -f elf "./kernel/kernel_entry.asm" -o "./bin/kernel_entry.o"

#kernel

i386-elf-gcc ${CC_FLAGS} "./kernel/kernel.c" -o "./bin/kernel.o"

i386-elf-gcc ${CC_FLAGS} "./graphics/draw/draw.c" -o "./bin/draw.o"

i386-elf-gcc ${CC_FLAGS} "./graphics/font/print.c" -o "./bin/print.o"

i386-elf-gcc ${CC_FLAGS} "./Include/string.c" -o "./bin/string.o"

i386-elf-gcc ${CC_FLAGS} "./Include/IoPorts.c" -o "./bin/IoPorts.o"

i386-elf-gcc ${CC_FLAGS} "./Include/malloc.c" -o "./bin/malloc.o"

i386-elf-gcc ${CC_FLAGS} "./graphics/screen/screen.c" -o "./bin/screen.o"

i386-elf-gcc ${CC_FLAGS} "./Include/time.c" -o "./bin/time.o"

i386-elf-gcc ${CC_FLAGS} "./event_handler/event_handler.c" -o "./bin/event_handler.o"

i386-elf-gcc ${CC_FLAGS} "./event_handler/event_queue.c" -o "./bin/event_queue.o"

i386-elf-gcc ${CC_FLAGS} "./Hardware/keyboard/keyboard.c" -o "./bin/keyboard.o"

i386-elf-gcc ${CC_FLAGS} "./Hardware/mouse/mouse.c" -o "./bin/mouse.o"

i386-elf-gcc ${CC_FLAGS} "./Hardware/cpu/cpu.c" -o "./bin/cpu.o"

i386-elf-gcc ${CC_FLAGS} "./terminal/terminal.c" -o "./bin/terminal.o"

#inrerrupts

nasm -f elf "./Interrupts/interrupts.asm" -o "./bin/interrupts.o"

i386-elf-gcc ${CC_FLAGS} "./Interrupts/idt.c" -o "./bin/idt.o"

i386-elf-gcc ${CC_FLAGS} "./Interrupts/irq.c" -o "./bin/irq.o"

i386-elf-gcc ${CC_FLAGS} "./Interrupts/isr.c" -o "./bin/isr.o"

#filesystem

i386-elf-gcc ${CC_FLAGS} "./filesystem/filesystem.c" -o "./bin/filesystem.o"

#PCI

i386-elf-gcc ${CC_FLAGS} "./PCI/pci.c" -o "./bin/pci.o"

#final build

#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           #

i386-elf-ld -T "./linker.ld" -o "./bin/kernel32.elf" "./bin/kernel_entry.o" "./bin/kernel.o" \
    "./bin/cpu.o"                       \
    "./bin/IoPorts.o"                   \
    "./bin/string.o"                    \
    "./bin/malloc.o"                    \
    "./bin/interrupts.o"                \
    "./bin/idt.o"                       \
    "./bin/irq.o"                       \
    "./bin/isr.o"                       \
    "./bin/filesystem.o"                \
    "./bin/pci.o"                       \
    "./bin/screen.o"                    \
    "./bin/time.o"                      \
    "./bin/draw.o"                      \
    "./bin/print.o"                     \
    "./bin/event_queue.o"               \
    "./bin/event_handler.o"             \
    "./bin/keyboard.o"                  \
    "./bin/mouse.o"                     \
    "./bin/terminal.o"                  \
    --Map="./a_debug/kernel32_map.txt"


i386-elf-objdump -s "./bin/kernel32.elf" > "./a_debug/kernel32_hexdump.txt"

#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           #

i386-elf-objcopy -O binary "./bin/kernel32.elf" "./bin/kernel32.bin"

#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           

# Place first stage starting at sector 1 (LBA=0)

dd if="./bin/stage1_bootloader.bin" of="./bin/os.img" bs=512

# Place second stage starting at sector 2 (LBA=1)

dd if="./bin/stage2_bootloader.bin" of="./bin/os.img" bs=512 seek=1

# Place kernel starting at sector 6 (LBA=5)

dd if="./bin/kernel32.bin" of="./bin/os.img" bs=512 seek=5

# Extend the os.img to the size of a 1.44M floppy (can be useful)

truncate -s 1440k "./bin/os.img"                                    # NOT MADE BY ME. CREDITS TO sixteenlettername: https://www.reddit.com/r/osdev/comments/1ikv5ma/pm32_bit_confusing_c_printing_problem/

#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           #

#run

qemu-system-i386 -drive format=raw,file="./bin/os.img" -d cpu_reset,int -D "./a_debug/qemu_interrupt_log.txt" -m 1G