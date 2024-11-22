/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <stdint.h>
#include "types.h"

/* Define memory boundary constants */
#define MEM_ROM_BANK_END  0x8000
#define MEM_VRAM_END      0xA000
#define MEM_EXRAM_END     0xC000
#define MEM_WRAM_END      0xD000
#define MEM_WRAM_BANK_END 0xE000
#define MEM_ECHRAM_END    0xFE00
#define MEM_OAM_END       0xFEA0
#define MEM_UNUSABLE_END  0xFF00
#define MEM_IOREG_END     0xFF80
#define MEM_HRAM_END      0xFFFF

/* Define bus read/write functions for mappings */
uint8_t bus_read(context_t* ctx, uint16_t addr);
void bus_write(context_t* ctx, uint16_t addr, uint8_t byte);
