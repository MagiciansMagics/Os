#ifndef _IOPORTS_H_
#define _IOPORTS_H_

#pragma once

#include <stdint.h>
#include <stddef.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif