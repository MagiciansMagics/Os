#ifndef _SCREEN_H_
#define _SCREEN_H_

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../Include/malloc.h"

void screen_init();
void SwapBuffers();
void handle_screen();

#endif