#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdint.h>
#include <stddef.h>
#include "../Include/string.h"
#include "../graphics/font/print.h"
#include "../graphics/draw/draw.h"

#pragma once

void handle_terminal_cmd(char* command);

#endif