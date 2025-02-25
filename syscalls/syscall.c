#include "./syscall.h"

int syscall(int num, unsigned int arg1, unsigned int arg2, unsigned int arg3)
{
    int ret;
    asm volatile 
    (
        "int $0x80"
        : "=a"(ret)
        : "a"(num), "b"(arg1), "c"(arg2), "d"(arg3)
    );
    return ret;
}

void write(const char* message) 
{
    syscall(SYS_WRITE, (unsigned int)message, 0, 0);
}