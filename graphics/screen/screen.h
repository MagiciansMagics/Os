#ifndef _SCREEN_H_
#define _SCREEN_H_

#include <stdint.h>
#include <stddef.h>
#include "../../Include/malloc.h"
#include "../../Include/string.h"
#include "../../Interrupts/irq.h"
#include "../../Include/IoPorts.h"

#pragma once

#define WSCREEN 1920
#define HSCREEN 1080
#define BPP     32

void handle_screen();
void init_screen();
uint32_t *return_framebuffer();

#endif