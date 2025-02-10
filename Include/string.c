#include "./string.h"

void* memset(void* dest, unsigned char val, size_t count)
{ 
    if (!dest) return NULL;

	unsigned char* destC = (unsigned char*)dest;
	int i;
	for (i = 0; i < count; i++)
		destC[i] = val;
	return dest;
}

void *memcpy(void *dst, const void *src, uint32_t len)
{
    for (uint32_t i = 0; i < len; i++)
        ((uint8_t *)dst)[i] = ((uint8_t *)src)[i];

    return dst;
}

// Convertations

char* itoa(int value, char* str, int base) 
{
    int i = 0;
    int isNegative = 0;

    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (value < 0 && base == 10) {
        isNegative = 1;
        value = -value;
    }

    while (value != 0) {
        int rem = value % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        value = value / base;
    }

    if (isNegative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    // Reverse the string
    for (int start = 0, end = i - 1; start < end; start++, end--) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
    }

    return str;
}