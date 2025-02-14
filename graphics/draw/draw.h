#ifndef _DRAW_H_
#define _DRAW_H_

#include <stdint.h>
#include <stddef.h>

#pragma once

#define WSCREEN 1920
#define HSCREEN 1080
#define BPP     32

void draw_pixel(uint16_t x, uint16_t y, uint32_t color);
uint32_t rgba_to_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif