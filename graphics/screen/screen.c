#include "./screen.h"

uint32_t *framebuffer = NULL;

void init_screen()
{
    if (!framebuffer)           // basicly just make sure framebuffer is null when setting up
        framebuffer = (uint32_t *)(*(uint32_t *)0x1028);
}

uint32_t *return_framebuffer()
{
    return framebuffer;
}