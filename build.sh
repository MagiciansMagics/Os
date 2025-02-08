clear
export PATH=/usr/local/i386elfgcc/bin:$PATH
rm -rf bin/
mkdir bin/

CC_FLAGS="-g -m32 -ffreestanding -fno-pic -c"

# bootloader
nasm -f bin "./bootloader/stage1/stage1_bootloader.asm" -o "./bin/stage1_bootloader.bin"
nasm -f bin "./bootloader/stage2/stage2_bootloader.asm" -o "./bin/stage2_bootloader.bin"
nasm -f elf "./kernel/kernel_entry.asm" -o "./bin/kernel_entry.o"

#kernel

i386-elf-gcc ${CC_FLAGS} "./kernel/kernel.c" -o "./bin/kernel.o"

i386-elf-gcc ${CC_FLAGS} "./graphics/draw/draw.c" -o "./bin/draw.o"

i386-elf-gcc ${CC_FLAGS} "./graphics/font/print.c" -o "./bin/print.o"

#final build

#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           #


i386-elf-ld -T "./linker.ld" -o "./bin/kernel32.elf" "./bin/kernel_entry.o" "./bin/kernel.o" \
    "./bin/draw.o"                      \
    "./bin/print.o"



#           ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;           #

i386-elf-objcopy -O binary "./bin/kernel32.elf" "./bin/kernel32.bin"

cat "./bin/stage1_bootloader.bin" "./bin/stage2_bootloader.bin" > "./bin/bootloader.bin"

cat "./bin/bootloader.bin" "./bin/kernel32.bin" > "./bin/os.bin"

dd if="./bin/os.bin" of="./bin/os.img" bs=512

#run

qemu-system-i386 -drive format=raw,file="./bin/os.img"