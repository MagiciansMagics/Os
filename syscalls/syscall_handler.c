#include "./syscall.h"

extern void syscall_entry();

struct trap_frame {
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esi;
    unsigned int edi;
    unsigned int ebp;
    unsigned int ds;
    unsigned int es;
    unsigned int fs;
    unsigned int gs;
    unsigned int esp;
};

void syscall_handler(struct trap_frame *frame) 
{
    const unsigned int num = frame->eax;

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