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

int syscall_exit(int error_code)
{
    return syscall(SYS_EXIT, error_code, 0, 0);
}

// Filesystem stuff

int syscall_creat(char* filename, int flags)
{
    return syscall(SYS_CREAT, (unsigned int)filename, flags, 0);
}

int syscall_rmv(char* filename)
{
    return syscall(SYS_RMV, (unsigned int)filename, 0, 0);
}

int syscall_mkdir(char* dirname, int permissions)
{
    return syscall(SYS_MKDIR, (unsigned int)dirname, permissions, 0);
}

int syscall_rmdir(char* dirname)
{
    return syscall(SYS_RMDIR, (unsigned int)dirname, 0, 0);
}