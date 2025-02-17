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

int16_t strcmp(const uint8_t *string1, const uint8_t *string2)
{
    while (*string1 && *string1 == *string2) {
        string1++;
        string2++;
    }

    return *string1 - *string2;
}

uint8_t *strncpy(uint8_t *dst, const uint8_t *src, const uint8_t len)
{
    for (uint8_t i = 0; src[i] && i < len; i++)
        dst[i] = src[i];

    return dst;
}

uint8_t strlen(const uint8_t *string)
{
    uint8_t len = 0;

    while (*string) {
        string++;
        len++;
    }

    return len;
}

char* strcat(char* dest, const char* src) 
{
    char* ptr = dest;

    while (*ptr != '\0') 
    {
        ptr++;
    }

    while (*src != '\0') 
    {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}