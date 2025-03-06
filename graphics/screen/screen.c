#include "./screen.h"
#include "../draw/draw.h"

uint32_t *framebuffer = NULL;

uint32_t front_buffer[WSCREEN * HSCREEN];

void copy_memory(void *dest, const void *src, size_t n)
{
    uint8_t *d = (uint8_t *)dest;
    const uint8_t *s = (const uint8_t *)src;

    // Copy byte by byte
    for (size_t i = 0; i < n; i++) 
    {
        d[i] = s[i];
    }
}

void handle_screen()
{
    while (1)
    {
        front_buffer[10 * 1920 + 10] = rgba_to_hex(255, 255, 255, 255);

        copy_memory(framebuffer, front_buffer, WSCREEN * HSCREEN);
    }
}

void init_screen()
{
    if (!framebuffer)           // basicly just make sure framebuffer is null when setting up
        framebuffer = (uint32_t *)(*(uint32_t *)0x1028);

    clear_screen(rgba_to_hex(0, 0, 0, 255));    
}

uint32_t *return_framebuffer()
{
    return framebuffer;
}