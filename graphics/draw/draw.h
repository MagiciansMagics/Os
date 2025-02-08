#ifndef _DRAW_H_
#define _DRAW_H_

#pragma once

#include <stdint.h>
#include <stddef.h>

#define WSCREEN 1920
#define HSCREEN 1080

void draw_pixel(uint16_t x, uint16_t y, uint32_t color);

uint32_t rgba_to_hex(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif