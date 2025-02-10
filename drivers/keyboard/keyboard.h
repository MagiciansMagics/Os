#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "../../Include/IoPorts.h"
#include "../../Interrupts/irq.h"

#pragma once

#define MAX_TEXT_SIZE 1000           // max allowed to write per text section

void InitKeyboard();

#endif