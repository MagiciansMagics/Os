#ifndef _CPU_H_
#define _CPU_H_

#include <stdint.h>

#pragma once

void get_cpu_vendor(char* vendor);
void get_cpu_model_info(uint32_t* family, uint32_t* model, uint32_t* stepping);
void get_cpu_features(uint32_t* ecx_flags, uint32_t* edx_flags);

#endif