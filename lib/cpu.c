/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "cpu.h"

/*
 * @brief Fetch instruction from memory for 
 * cpu processing
 *
 * @param ctx Emulator context
 */
static inline void fetch(context_t* ctx)
{
    GET_REGS(ctx);

    uint16_t opcode = ctx->rom[pc];

    ctx->cpu.opcode = (opcode >> 8); 

    printf("0x%x\n", opcode);
}

/*
 * @brief Decode instruction from fetch for 
 * cpu callback
 *
 * @param ctx Emulator context
 */
static inline void decode(context_t* ctx)
{

}

/*
 * @brief Execute decoded instruction
 *
 * @param ctx Emulator context
 */
static inline void execute(context_t* ctx)
{

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
}

/*
 * @brief Loop cycles until gabe exits
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
