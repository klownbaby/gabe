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
#include <stdbool.h>

/*
 * @brief Checks whether a CPU flag is enabled or
 * disabled by masking the flag register
 *
 * @param flag The flag (bit) to check
 */
#define CPU_FLAG_CHECK(flag, ...)

/* Define register macros for readability */
#define REG8    uint8_t
#define REG16   uint16_t

/*
 * @brief Structure for holding all emulator-related
 * context for use throughout gabe
 */
typedef struct {
    /* Keep track of cylce count */
    uint32_t cycles;

    /* CPU register definitions */
    struct {
        /* General purpose registers */
        REG8 a;
        REG8 f;          /* < Flags */
        REG8 b;
        REG8 c;
        REG8 d;
        REG8 e;
        REG8 h;
        REG8 l;

        /* Word-sized special registers */
        REG16 sp;        /* < Stack pointer */
        REG16 pc;        /* < Program counter */
    } regs;

    uint16_t fetched;
    uint16_t mdest;

    uint8_t opcode;

    bool halted;
} cpu_t;

typedef struct {
    cpu_t cpu; 

    bool running;
} context_t;
