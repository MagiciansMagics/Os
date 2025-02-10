#ifndef _MALLOC_H_
#define _MALLOC_H_

#pragma once

#include <stddef.h>
#include <stdint.h>
#include "../graphics/font/print.h"

#define MEM_POOL_SIZE (1024 * 1024)                     // 1 MB
#define MAX_ALLOC_SIZE (MEM_POOL_SIZE * 500)            // 500 MB
#define BLOCK_SIZE sizeof(malloc_header_t)

typedef struct malloc_header_t
{
    uint32_t size;
    uint32_t used;
    struct malloc_header_t* next;
    struct malloc_header_t* prev;
} malloc_header_t;

void Memory_Init();
void *AllocateMemory(size_t size);
void DeallocateMemory(void *ptr);

#endif