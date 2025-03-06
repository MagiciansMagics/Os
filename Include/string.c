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

int memcmp(const void* ptr1, const void* ptr2, size_t num)
{
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;

    while (num--)
    {
        if (*p1 != *p2)
            return *p1 - *p2;
        
        p1++;
        p2++;
    }

    return 0;
}

void *memcpy(void *dst, const void *src, uint32_t len)
{
    uint32_t *dword_dst = (uint32_t *)dst;
    const uint32_t *dword_src = (const uint32_t *)src;

    while (len >= 4) {
        *dword_dst = *dword_src;
        dword_dst++;
        dword_src++;
        len -= 4;
    }

    uint8_t *byte_dst = (uint8_t *)dword_dst;
    const uint8_t *byte_src = (const uint8_t *)dword_src;
    while (len > 0) {
        *byte_dst = *byte_src;
        byte_dst++;
        byte_src++;
        len--;
    }

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

char *strncpy(char *dest, const char *src, size_t n)
{
    size_t i;
    for (i = 0; i < n && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    for (; i < n; i++)
    {
        dest[i] = '\0';
    }

    return dest;
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

char* strncat(char* dest, const char* src, size_t n)
{
    char* d = dest;
    const char* s = src;

    while (*d != '\0') 
    {
        d++;
    }

    while (n-- && *s != '\0')
    {
        *d++ = *s++;
    }

    *d = '\0';

    return dest;
}

char* strrchr(const char* str, int c)
{
    char* last_occurrence = NULL;

    while (*str != '\0')
    {
        if (*str == (char)c)
        {
            last_occurrence = (char*)str;
        }
        str++;
    }

    return last_occurrence;
}