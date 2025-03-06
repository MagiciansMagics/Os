#include "./syscall.h"
#include "../graphics/screen/screen.h"

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

int syscall_handler(struct trap_frame *frame) 
{
    const unsigned int num = frame->eax;

    switch (num) 
    {
        case SYS_EXIT:
        {
            return (int)frame->ebx;
        }

        case SYS_CREAT:
        {
            char* filename = (char*)frame->ebx;
            int flags = (int)frame->ecx;

            int i = create_file(filename, flags);

            return i;
        }

        case SYS_RMV:
        {
            char* filename = (char*)frame->ebx;

            int i = remove_file(filename);

            return i;
        }

        case SYS_MKDIR:
        {
            char* dirname = (char*)frame->ebx;
            int permissions = (int)frame->ecx;

            int i = create_directory(dirname, permissions);

            return i;
        }

        case SYS_RMDIR:
        {
            char* dirname = (char*)frame->ebx;

            int i = remove_directory(dirname);

            return i;
        }

        default:
        {
            return 1;
        }
    }
}

void init_syscalls() 
{
    idt_set_gate(0x80, (unsigned int)syscall_entry, 0x08, 0x8E); // Ring 0 access. Ring 3: 0xEE i guess
}