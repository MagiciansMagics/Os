#ifndef _PRINT_H
#define _PRINT_H

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../../Include/string.h"
#include "../../event_handler/event_queue.h"

void put_char(char c, uint32_t color);
void put_string(const char* str, uint32_t color);
void print(const char *fmt, ...);
void set_print_x_pos(int x);
void set_print_y_pos(int y);
int get_print_x_pos();
int get_print_y_pos();
void set_print_color(uint32_t color);

#endif