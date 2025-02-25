[BITS 16]
[ORG 0x7c00]

jmp _start

%include "./bootloader/include/halt.asm"

%include "./bootloader/include/print16.asm"

%include "./bootloader/include/disk_read16.asm"

_start:
    mov [drive_number], dl

    cli
	mov ax, 0x00
	mov ds, ax
	mov es, ax
	mov ss, ax
	mov sp, 0x7C00
	sti

    xor bx, bx
    mov es, bx

    mov ah, 0x00
    mov al, 0x03
    int 0x10

    mov al, 0x04                                ; AL = number of sectors to read	(1-128 dec.)
	mov ch, 0x00                                ; CH = track/cylinder number  (0-1023 dec., see below)
	mov cl, 0x02                                ; CL = sector number  (1-17 dec.)
    mov dh, 0x00                                ; DH = head number  (0-15 dec.)
    mov bx, 0x7e00                              ; BX = what address to load the read sectors
    call disk_read16                            ; Function that my magical hands made

    mov al, 0x80                                ; AL = number of sectors to read	(1-128 dec.)
	mov ch, 0x00                                ; CH = track/cylinder number  (0-1023 dec., see below)
	mov cl, 0x06                                ; CL = sector number  (1-17 dec.)
    mov dh, 0x00                                ; DH = head number  (0-15 dec.)
    mov bx, 0x9000                              ; BX = what address to load the read sectors
    call disk_read16                            ; Function that my magical hands made

    jmp 0x7e00

    jmp halt

drive_number: db 0

times 510 - ($-$$) db 0
dw 0xAA55