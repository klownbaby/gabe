/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "cpu.h"
#include "bus.h"


/*
 * @brief Internal helper function for fetching the
 * next imeediate byte from ROM
 *
 * @param ctx Emulator context
 */
static inline void fetch_imm(context_t* ctx)
{
    /* Increment program counter before fetch */
    INC_PC;
    
    /* Get then ext byte and set in cpu context */
    ctx->cpu.cbyte = ctx->rom[REG(pc)];
}

/*
 * @brief NOP instruction for Z80 CPU
 * increments program counter
 *
 * @param ctx Emulator context
 */
callback_t __nop(context_t* ctx)
{
    return;
}


/*
 * @brief Load BC register with 16 bit 
 * immediate
 *
 * @param ctx Emulator context
 */
callback_t __ld_bc_imm16(context_t* ctx)
{
    /* Little endian so set MSB to C reg */
    fetch_imm(ctx);
    REG(c) = ctx->cpu.cbyte;

    /* Little endian so set LSB to B reg */
    fetch_imm(ctx);
    REG(b) = ctx->cpu.cbyte;
}

/*
 * @brief Load byte pointed to by BC
 * register with value in register A
 *
 * @param ctx Emulator context
 */
callback_t __ld_pbc_a(context_t* ctx)
{
}

/*
 * @brief Increment BC register
 *
 * @param ctx Emulator context
 */
callback_t __inc_bc(context_t* ctx)
{
}

/*
 * @brief Increment A register
 *
 * @param ctx Emulator context
 */
callback_t __inc_a(context_t* ctx)
{
    /* Increment A */
    ++REG(a);
}

/*
 * @brief Decrement B register
 *
 * @param ctx Emulator context
 */
callback_t __dec_b(context_t* ctx)
{
    /* Decrement B */
    --REG(b);
}
