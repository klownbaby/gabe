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
 * @brief Callback locked macro for manipulating registers
 *
 * Since only instructions should be manipulating registers,
 * this is defined in the source, in order to limit misuse
 *
 * @param ctx Emulator context
 */
#define REG(reg) ctx->cpu.regs.reg

/*
 * @brief NOP instruction for Z80 CPU
 * increments program counter
 *
 * @param ctx Emulator context
 */
callback_t __nop(context_t* ctx)
{
    /* 
     * NOP instruction, we just want to increment the
     * program counter, nothing else
     *
     * We can map this to an actual nop instruction on native
     * hardware
     */
    asm volatile ("nop");
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
