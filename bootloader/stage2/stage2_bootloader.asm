[BITS 16]
[ORG 0x7e00]

jmp _start

%include "./bootloader/include/halt.asm"

%include "./bootloader/include/gdt32.asm"

%include "./bootloader/include/vbe_screen_mode.asm"

_start:
	call vbe_screen_mode
	cli
	lgdt[gdt_descriptor]
	mov eax, cr0
	or al, 0x01
	mov cr0, eax
	jmp CODE_SEG:_start32

    jmp halt


[BITS 32]
_start32:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	;set up the stack
	mov ebp, 0x90000
	mov esp, ebp

	mov esi, mode_info_block
    mov edi, 0x9000
    mov ecx, 64                 ; Mode info block is 256 bytes / 4 = # of dbl words
    rep movsd

    jmp 0x9000

    jmp halt

times 1024 - ($-$$) db 0

%include "./bootloader/include/vbe_blocks.asm"