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
#define REG8    volatile uint8_t
#define REG16   volatile uint16_t

/* Define optional macro for optional functions so compiler happy */
#define OPTIONAL __attribute__((used))

typedef struct {
    /* General purpose registers */
    REG8 a;
    REG8 b;
    REG8 c;
    REG8 d;
    REG8 e;
    REG8 h;
    REG8 l;

    REG8 f : 4;          /* < Flags */

    /* Word-sized 'special' registers */
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

    /* Current byte */
    uint16_t cbyte;
    
    /* Current opcode */
    uint8_t opcode;

    /* Is the emulator paused (halted)? */
    bool halted;
} cpu_t;

/*
 * @brief Contains cartridge header info read 
 * from ROM
 */
typedef struct {
    /* Entry and logo */
    uint8_t entry[4];
    uint8_t logo[48];

    /* Game title */
    char title[16];

    /* New licensee code */
    uint16_t nlic;

    /* Other important cart info */
    uint8_t cgb;
    uint8_t type;
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t dest;
    uint8_t lic;
    uint8_t version;

    /* Checksums (standard and global) */
    uint8_t checksum;
    uint8_t g_checksum;
} cart_header_t;

/*
 * @brief Structure for holding global emulator-related
 * context for use throughout gabe
 */
typedef struct {
    /* All cpu context is stored seperately */
    cpu_t cpu; 

    /* Cartridge header info */
    cart_header_t header;

    /* Memory map */
    uint8_t* rbanks[10];
    uint8_t* rom;
    uint8_t* vram;
    uint8_t* exram;
    uint8_t* wram;
    uint8_t* echram;
    uint8_t* oam;
    uint8_t* io;
    uint8_t* hram;

    /* Emulator state flags */
    bool interrupt_enable;
    bool running;
} context_t;

/* Formatting these as macros for readability */
typedef void callback_t;
typedef callback_t (*callback_fp_t)(context_t* ctx);
