#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <stdint.h>
#include <stddef.h>
#include "../../graphics/screen/screen.h"
#include "../../Include/IoPorts.h"
#include "../../Interrupts/irq.h"
#include "../../graphics/draw/draw.h"

#pragma once

void init_mouse();
void draw_mouse(int mouse_x, int mouse_y, uint32_t color);

#endif