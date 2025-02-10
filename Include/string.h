#ifndef _STRING_H
#define _STRING_H

#pragma once

#include <stdint.h>
#include <stddef.h>

void* memset(void* dest, unsigned char val, size_t count);
void *memcpy(void *dst, const void *src, const uint32_t len);
char* itoa(int value, char* str, int base);

#endif