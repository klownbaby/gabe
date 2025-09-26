/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include "constants.h"

/* Contiguous memory refernce */
extern uint8_t __contiguous[0xFFFF];

/* Memory map, 4K aligned references */
extern uint8_t __rb16[_16K];
extern uint8_t __rb16_sw[_16K]; /* Switchable 16k rom bank */
extern uint8_t __vram[_8K];
extern uint8_t __extram[_8K];
extern uint8_t __wram_sw[_8K];  /* Switchable 8k work ram bank */
extern uint8_t __wram[_8K];

/* Unaligned memory references */
extern uint8_t __echo[0x1DFF];  /* Mirror of 0xC000-0xDDFF */
extern uint8_t __oam[0x9F];
extern uint8_t __reserved[0x5F];
extern uint8_t __io_reg[0x7F];
extern uint8_t __hram[0x7E];
extern uint8_t __int_en[0x1];   /* Interrupt enable register */
