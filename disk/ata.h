#ifndef _AHCI_H_
#define _AHCI_H_

#include <stdint.h>
#include <stdbool.h>
#include "../Include/IoPorts.h"

#pragma once

#define STATUS_BSY      0x80
#define STATUS_RDY      0x40
#define STATUS_DRQ      0x08
#define STATUS_DF       0x20
#define STATUS_ERR      0x01

#endif