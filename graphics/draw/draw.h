#ifndef _DRAW_H_
#define _DRAW_H_

#include <stdint.h>
#include <stddef.h>
#include "../screen/screen.h"

#pragma once

int draw_pixel(uint16_t x, uint16_t y, uint32_t color);
void clear_screen(uint32_t color);
void draw_rectangular(int x, int y, int width, int height, uint32_t color);
uint32_t return_pixel_color(int x, int y);
uint32_t rgba_to_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif