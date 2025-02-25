#include "./syscall.h"

extern void syscall_entry();

void syscall_handler(int num, unsigned int arg1, unsigned int arg2, unsigned int arg3) 
{
    switch (num) 
    {
        case 1:
            print("Passed\n");
            break;

        default:
            print("Invalid syscall!\n");
            print("Syscall number: %d\n", num);
            break;
    }
}

void init_syscalls() 
{
    idt_set_gate(0x80, (unsigned int)syscall_entry, 0x08, 0x8E); // Ring 0 access. Ring 3: 0xEE i guess
}