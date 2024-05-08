
/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <stdbool.h>
#include <stdint.h>

/* Define register macros for readability */
#define REG8    uint8_t
#define REG16   uint16_t

typedef struct {
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
} registers_t;

/*
 * @brief Structure for holding all cpu-related
 * context for use throughout gabe
 */
typedef struct {
    /* Keep track of cylce count */
    uint32_t cycles;

    /* CPU register definitions */
    registers_t regs;

    uint16_t fetched;
    uint16_t mdest;

    uint8_t opcode;

    bool halted;
} cpu_t;

/*
 * @brief Structure for holding global emulator-related
 * context for use throughout gabe
 */
typedef struct {
    cpu_t cpu; 

    uint16_t* rbanks[10];
    uint16_t* vram;
    uint16_t* exram;
    uint16_t* wram;
    uint16_t* echram;
    uint16_t* oam;
    uint16_t* io;
    uint16_t* hram;

    bool interrupt_enable;
    bool running;
} context_t;

/* Formatting these as macros for readability */
typedef void (*CALLBACKFP)(context_t* ctx);
typedef void CALLBACK;
