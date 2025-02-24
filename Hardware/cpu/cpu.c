#include "./cpu.h"

#include <stdint.h>

void cpuid(uint32_t leaf, uint32_t subleaf, uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) 
{
    __asm__ volatile ("cpuid"
                      : "=a"(*a), "=b"(*b), "=c"(*c), "=d"(*d)
                      : "a"(leaf), "c"(subleaf));
}

void get_cpu_vendor(char* vendor) 
{
    uint32_t eax, ebx, ecx, edx;

    cpuid(0, 0, &eax, &ebx, &ecx, &edx);

    *((uint32_t*)&vendor[0]) = ebx;
    *((uint32_t*)&vendor[4]) = edx;
    *((uint32_t*)&vendor[8]) = ecx;
    vendor[12] = '\0';
}

void get_cpu_model_info(uint32_t* family, uint32_t* model, uint32_t* stepping) 
{
    uint32_t eax, ebx, ecx, edx;
    
    cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    *stepping = eax & 0xF;
    *model = ((eax >> 4) & 0xF) | ((eax >> 12) & 0xF0);
    *family = ((eax >> 8) & 0xF) + ((eax >> 20) & 0xFF);
}

void get_cpu_features(uint32_t* ecx_flags, uint32_t* edx_flags) 
{
    uint32_t eax, ebx, ecx, edx;

    cpuid(1, 0, &eax, &ebx, &ecx, &edx);

    *ecx_flags = ecx;
    *edx_flags = edx;
}