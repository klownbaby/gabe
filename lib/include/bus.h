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

#define ROM_STATS_IDX       0
#define VRAM_STATS_IDX      1
#define EXRAM_STATS_IDX     2
#define WRAM_STATS_IDX      3
#define WRAM_BANK_STATS_IDX 4
#define ECHRAM_STATS_IDX    5
#define OAM_STATS_IDX       6
#define UNUSABLE_STATS_IDX  7
#define IOREG_STATS_IDX     8
#define HRAM_STATS_IDX      9

/*
 * @brief Dump all bus read-related stats
 * for debugging purposes
 *
 * @param cond Condition to assert
 */
#define DUMP_BUS_READS() \
    do {           \
        printf("ROM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);       \
        printf("VRAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);      \
        printf("EXRAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);     \
        printf("WRAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);      \
        printf("WRAM Bank Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]); \
        printf("ECHRAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);    \
        printf("OAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);       \
        printf("UNUSABLE Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);  \
        printf("IOREG Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);     \
        printf("HRAM Reads = %lu\n", bus_read_stats[ROM_STATS_IDX]);      \
    } while (0)


/* Define bus read/write functions for mappings */
uint8_t bus_read(context_t* ctx, uint16_t addr);
void bus_write(context_t* ctx, uint16_t addr, uint8_t byte);
