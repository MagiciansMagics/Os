#ifndef _PRINT_H
#define _PRINT_H

#pragma once

#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../../Include/string.h"

void put_char(char c, uint32_t color);
void put_string(const char* str, uint32_t color);
void print(const char *fmt, ...);

#endif