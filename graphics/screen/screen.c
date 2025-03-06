#include "./screen.h"
#include "../draw/draw.h"

uint32_t *framebuffer = NULL;

uint32_t front_buffer[WSCREEN * HSCREEN];
uint32_t back_buffer[WSCREEN * HSCREEN];

void swap_buffers()
{
    if (memcmp(front_buffer, back_buffer, WSCREEN * HSCREEN * sizeof(uint32_t)) != 0) 
    {
        memcpy(front_buffer, back_buffer, WSCREEN * HSCREEN * sizeof(uint32_t));
        memcpy(framebuffer, front_buffer, WSCREEN * HSCREEN * sizeof(uint32_t)); // both of these are mandatory, one copies the backbuffer 
                                                                                 // to the front buffer and front buffer is copied to frambuffer
    }
}

void handle_screen()
{
    swap_buffers();
}

void init_screen()
{
    if (!framebuffer)           // basicly just make sure framebuffer is null when setting up
        framebuffer = (uint32_t *)(*(uint32_t *)0x1028);

    memset(front_buffer, 0, WSCREEN * HSCREEN * sizeof(uint32_t));
    memset(back_buffer, 0, WSCREEN * HSCREEN * sizeof(uint32_t));

    clear_screen(rgba_to_hex(0, 0, 0, 255));    
}

uint32_t *return_framebuffer()
{
    return back_buffer;
}