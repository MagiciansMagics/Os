vbe_screen_mode:
    mov ah, 0x00
    mov al, 0x03
    int 0x10

    xor ax, ax
    mov es, ax
    mov ah, 4Fh
    mov di, vbe_info_block
    int 10h

    cmp ax, 4Fh
    jne error

    mov ax, word [vbe_info_block.video_mode_pointer]
    mov [offset], ax
    mov ax, word [vbe_info_block.video_mode_pointer+2]
    mov [t_segment], ax
        
    mov fs, ax
    mov si, [offset]

    ;; Get next VBE video mode
    .find_mode:
        mov dx, [fs:si]
        inc si
        inc si
        mov [offset], si
        mov [mode], dx

        cmp dx, word 0FFFFh	        ; at end of video mode list?
        je end_of_modes

        mov ax, 4F01h		        ; get vbe mode info
        mov cx, [mode]
        mov di, mode_info_block		; Mode info block mem address
        int 10h

        cmp ax, 4Fh
        jne error

        mov ax, [width]
        cmp ax, [mode_info_block.x_resolution]
        jne .next_mode

        mov ax, [height]					
        cmp ax, [mode_info_block.y_resolution]
        jne .next_mode

        mov ax, [bpp]
        cmp al, [mode_info_block.bits_per_pixel]
        jne .next_mode
        
        mov ax, 4F02h	; Set VBE mode
        mov bx, [mode]
        or bx, 4000h	; Enable linear frame buffer, bit 14
        xor di, di
        int 10h

        cmp ax, 4Fh
        jne error

        ret
    .next_mode:
        mov ax, [t_segment]
        mov fs, ax
        mov si, [offset]
        jmp .find_mode

    error:
        cli
        hlt

    end_of_modes:
        cli
        hlt

width: dw 1920
height: dw 1080
bpp: db 32
offset: dw 0
t_segment: dw 0	; "segment" is keyword in fasm
mode: dw 0