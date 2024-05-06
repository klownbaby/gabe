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

#define CPU_FLAG_CHECK(flag, ...)

/*
 * @brief Structure for holding all emulator-related
 * context for use throughout gabe
 */
typedef struct {
    /* Keep track of cylce count */
    uint32_t cycles;

    /* CPU registers */
    struct {
        /* 16 bit registers */
        uint16_t af;        /* < Accumulator and flags */
        uint16_t sp;        /* < Stack pointer */
        uint16_t pc;        /* < Program counter */

        /* 16 bit (8 bit optional) registers */
        union 
        {
            struct {
                uint8_t _b;
                uint8_t _c;
            };

            uint16_t all;
        } bc;

        union 
        {
            struct {
                uint8_t _d;
                uint8_t _e;
            };

            uint16_t all;
        } de;

        union 
        {
            struct {
                uint8_t _h;
                uint8_t _l;
            };

            uint16_t all;
        } hl;
    } regs;
} cpu_t;

typedef struct {
    /* CPU context */
    cpu_t cpu; 
    bool running;
} context_t;
