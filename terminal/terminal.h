#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <stdint.h>
#include <stddef.h>
#include "../Include/string.h"
#include "../graphics/font/print.h"
#include "../graphics/draw/draw.h"
#include "../filesystem/filesystem.h"
#include "../event_handler/event_queue.h"
#include "../Include/malloc.h"
#include "../Include/string.h"
#include "../Hardware/cpu/cpu.h"

#pragma once

#define MAX_ARGS 10

void handle_terminal_cmd(char* command);

#endif