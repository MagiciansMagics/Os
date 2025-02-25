#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <stdint.h>
#include <stddef.h>
#include "../Interrupts/idt.h"

#pragma once

#define SYS_WRITE  1

void init_syscalls();
int syscall(int num, unsigned int arg1, unsigned int arg2, unsigned int arg3);
void write(const char* message);

#endif