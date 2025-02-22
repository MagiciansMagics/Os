#ifndef _STRING_H
#define _STRING_H

#pragma once

#include <stdint.h>
#include <stddef.h>

void* memset(void* dest, unsigned char val, size_t count);
void *memcpy(void *dst, const void *src, const uint32_t len);
char* itoa(int value, char* str, int base);
int16_t strcmp(const uint8_t *string1, const uint8_t *string2);
char *strncpy(char *dest, const char *src, size_t n);
uint8_t strlen(const uint8_t *string);
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t n);
char* strrchr(const char* str, int c);

#endif