[BITS 32]
[GLOBAL _start]
[EXTERN main]

jmp _start

%include "./bootloader/include/halt.asm"

_start:
    call main
    
    jmp halt

times 512 - ($-$$) db 0