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
#include "types.h"

/*
 * @brief Checks whether a CPU flag is enabled or
 * disabled by masking the flag register
 *
 * @param flag The flag (bit) to check
 */
#define CPU_CHECK_FLAG(flag, ...)

/*
 * @brief Checks whether a CPU flag is enabled or
 * disabled by masking the flag register
 *
 * @param flag The flag (bit) to check
 */
#define GET_REGS(ctx) \
    REG8 a = ctx->cpu.regs.a; \
    REG8 b = ctx->cpu.regs.b; \
    REG8 c = ctx->cpu.regs.c; \
    REG8 d = ctx->cpu.regs.d; \
    REG8 e = ctx->cpu.regs.e; \
    REG8 f = ctx->cpu.regs.f; \
    REG8 h = ctx->cpu.regs.h; \
    REG8 l = ctx->cpu.regs.l; \
    REG16 sp = ctx->cpu.regs.sp; \
    REG16 pc = ctx->cpu.regs.pc; \

/*
 * @brief Increment the program counter given a 
 * cpu context
 */
#define INC_PC \
    ctx->cpu.regs.pc ++

CALLBACK nop(context_t* ctx);
