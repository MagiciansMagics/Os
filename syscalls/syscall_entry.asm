[GLOBAL syscall_entry]
[EXTERN syscall_handler]

section .text
syscall_entry:
    push gs         
    push fs
    push es
    push ds
    push ebp
    push edi
    push esi
    push edx
    push ecx
    push ebx
    push eax

    push esp
    call syscall_handler
    pop esp

    pop eax
    pop ebx
    pop ecx
    pop edx
    pop esi
    pop edi
    pop ebp
    pop ds
    pop es
    pop fs
    pop gs
    iret