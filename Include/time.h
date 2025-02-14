#ifndef TIMER_H
#define TIMER_H

#include "../Interrupts/idt.h"
#include "../Include/IoPorts.h"
#include "../Interrupts/irq.h"

#pragma once

void timer_phase(int hz);
void timer_handler(regs *r);
void time_init();
void sleep(int ticks);
#endif