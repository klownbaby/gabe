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


/* Define common size constants */
#define _16K 0x3FFF
#define _8K 0x1FFF
#define _4K 0xFFF

/*
 * @brief WIP! Macro for mapping addresses
 *
 * @param addr The mapped address region
 */
#define MAP_ADDR(addr)

/* Define static block of system memory */
static uint8_t __contiguous[0xFFFF];

/* Memory map, 4K aligned */
static uint8_t __rb16[_16K];
static uint8_t __rb16_sw[_16K]; /* Switchable 16k rom bank */
static uint8_t __vram[_8K];
static uint8_t __extram[_8K];
static uint8_t __wram[_8K];
static uint8_t __wram_sw[_8K];  /* Switchable 8k work ram bank */
static uint8_t __wram[_8K];

/* Unaligned memory */
static uint8_t __echo[0x1DFF];  /* Mirror of 0xC000-0xDDFF */
static uint8_t __oam[0x9F];
static uint8_t __reserved[0x5F];
static uint8_t __io_reg[0x7F];
static uint8_t __hram[0x7E];
static uint8_t __int_en[0x1];   /* Interrupt enable register */
