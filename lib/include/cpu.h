/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <stdio.h>
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
 * @brief Callback locked macro for manipulating registers
 *
 * Since only instructions should be manipulating registers,
 * this is defined in the source, in order to limit misuse
 *
 * @param reg register to access
 */
#define REG(reg) ctx->cpu.regs.reg

/*
 * @brief Calls an opcode's respective callback
 * based on the function pointer stored in the 
 * callbacks lookup table
 *
 * @param opcode Opcode to lookup
 * @param ctx Emulator context
 */
#define LOOKUP_CALLBACK(opcode, ctx) callbacks[opcode](ctx);

/*
 * @brief Construct word sized registers
 * from bitwise of 8 bit registers
 */
#define WORD_SIZE_REGS \
    REG16 af = (a << 8) | f; \
    REG16 bc = (b << 8) | c; \
    REG16 de = (d << 8) | e; \
    REG16 hl = (h << 8) | l; \

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
    WORD_SIZE_REGS;           \
    REG16 sp = ctx->cpu.regs.sp; \
    REG16 pc = ctx->cpu.regs.pc; \

/*
 * @brief Increment the program counter given a 
 * cpu context
 */
#define INC_PC \
    ++ctx->cpu.regs.pc

/*
 * @brief Increment the n times program counter 
 * given a cpu context
 */
#define INC_PC_N(n) \
    ctx->cpu.regs.pc += n

/*
 * @brief Prints out values of all CPU registers
 *
 * @param ctx Emulator context
 */
OPTIONAL static inline void register_dump(context_t* ctx)
{
    GET_REGS(ctx);

    /* Display general purpose registers */
    printf("\n\n** Register Dump **\n\n");
    printf("Current opcode=0x%x\n\n", 
           ctx->cpu.opcode);
    printf("\t-------------------\n");
    printf("\t| General Purpose |\n");
    printf("\t-------------------\n");
    printf("\tA = %x\n\tF = %x\n\tB = %x\n\tC = %x\n\tD = %x\n\tE = %x\n\tH = %x\n\tL = %x\n",
           a, f, b, c, d, e, h, l);

    /* Dispay word-sized 'special' registers */
    printf("\t-------------------\n");
    printf("\t|     Special     |\n");
    printf("\t-------------------\n");
    printf("\tSP=0x%x\n\tPC=0x%x\n\n", sp, pc);
}

/* Define core cpu functions */
void cycle(context_t* ctx);
void cycle_strict(context_t* ctx, uint8_t cycles);
void begin(context_t* ctx);

/* Define CPU instruction callbacks */
callback_t __nop(context_t* ctx);
callback_t __ld_bc_imm16(context_t* ctx);
callback_t __ld_pbc_a(context_t* ctx);
callback_t __inc_bc(context_t* ctx);
callback_t __inc_a(context_t* ctx);
callback_t __dec_b(context_t* ctx);

/* Instruction callback lookup table */
__attribute__((used)) static callback_fp_t callbacks[256] = {
    [0x0] = __nop,
    [0x10] = __ld_bc_imm16,
    [0xc3] = __inc_a,
    [0x50] = __dec_b
};
