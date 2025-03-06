#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <stdint.h>
#include <stddef.h>
#include "../Interrupts/idt.h"
#include "../graphics/font/print.h"
#include "../filesystem/filesystem.h"

#pragma once

typedef enum {
    SYS_EXIT = 1,
    SYS_CREAT = 8,
    SYS_RMV = 9,
    SYS_MKDIR = 27,
    SYS_RMDIR = 28,
} SYSCALL_NUMBERS;

void init_syscalls();
int syscall(int num, unsigned int arg1, unsigned int arg2, unsigned int arg3);

// actual system calls

int syscall_exit(int error_code);
int syscall_creat(char* filename, int flags);
int syscall_rmv(char* filename);
int syscall_mkdir(char* dirname, int permissions);
int syscall_rmdir(char* dirname);
int syscall_draw(int x, int y, uint32_t color);
int syscall_getdsp_data(int a[2]);

#endif