#include "./draw.h"

void draw_pixel(uint16_t x, uint16_t y, uint32_t color)
{
    uint32_t *framebuffer = return_framebuffer();
    uint32_t offset = y * WSCREEN + x;

    uint8_t src_a = (color >> 24) & 0xFF;
    uint8_t src_r = (color >> 16) & 0xFF;
    uint8_t src_g = (color >> 8) & 0xFF;
    uint8_t src_b = color & 0xFF;

    if (src_a == 255)
    {
        framebuffer[offset] = color;
        return;
    }

    uint32_t dest_color = framebuffer[offset];
    uint8_t dest_r = (dest_color >> 16) & 0xFF;
    uint8_t dest_g = (dest_color >> 8) & 0xFF;
    uint8_t dest_b = dest_color & 0xFF;

    uint8_t out_r = (src_r * src_a + dest_r * (255 - src_a)) / 255;
    uint8_t out_g = (src_g * src_a + dest_g * (255 - src_a)) / 255;
    uint8_t out_b = (src_b * src_a + dest_b * (255 - src_a)) / 255;

    framebuffer[offset] = (src_a << 24) | (out_r << 16) | (out_g << 8) | out_b;
}

void clear_screen(uint32_t color)
{
    for (int y = 0; y < HSCREEN; y++)
    {
        for (int x = 0; x < WSCREEN; x++)
        {
            draw_pixel(x, y, color);
        }
    }
}

uint32_t return_pixel_color(int x, int y)
{
    uint32_t *framebuffer = return_framebuffer();

    if (!framebuffer)
    {
        return 0;
    }

    if (x < 0 || x >= WSCREEN || y < 0 || y >= HSCREEN)
    {
        return 0;
    }

    return framebuffer[y * WSCREEN + x];
}


uint32_t rgba_to_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a) 
{
    return ((a << 24) + (r << 16) + (g << 8) + b);
}