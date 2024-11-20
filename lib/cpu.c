/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "cpu.h"
#include "debug.h"

/*
 * @brief Fetch instruction from memory for 
 * cpu processing
 *
 * @param ctx Emulator context
 */
static inline void fetch(context_t* ctx)
{
    /*
     * Fetch byte from rom in current emulator 
     * context at current program counter
     *
     * Then, set opcode in emulator context
     */
    ctx->cpu.cbyte = ctx->cpu.opcode = ctx->rom[REG(pc)];
}

/*
 * @brief Decode instruction from fetch for 
 * cpu callback
 *
 * @param ctx Emulator context
 */
static inline void decode(context_t* ctx)
{
    /* Ensure opcode has valid callback mapped */
    ASSERT(callbacks[ctx->cpu.opcode] != NULL, "Opcode callback exists");
}

/*
 * @brief Execute decoded instruction
 *
 * @param ctx Emulator context
 */
static inline void execute(context_t* ctx)
{
    /* Finally, find and call opcode's respective callback */
    LOOKUP_CALLBACK(ctx->cpu.opcode, ctx);
}

/*
 * @brief Cycle cpu while emulator is running
 *
 * @note This is part of the main execution loop for the cpu
 * and is arguably the most crucial part of gabe
 *
 * @param ctx Emulator context
 */
void cycle(context_t* ctx) 
{
    /* Fetch next instruction from ROM */
    fetch(ctx);

    /* Decode fetched instruciton into opcode */
    decode(ctx);

    /* Execute opcode */
    execute(ctx);

    /* Increment program counter after every instruction */
    INC_PC;
}

/*
 * @brief Cycle cpu for nCycles
 *
 * @param ctx Emulator context
 * @param nCycles Amount of cycles to run
 */
void cycle_strict(context_t* ctx, uint8_t cycles)
{
    /* Decrement cycle count until zero and cycle */
    while (cycles--) cycle(ctx);
}

/*
 * @brief Cycle cpu until gabe exits
 *
 * @param ctx Emulator context
 */
void begin(context_t* ctx)
{
    /* We want to cycle the cpu until interrupt/exit */
    while (ctx->running) {
        /* @see cycle() for more info */
        cycle(ctx);
    }
}
