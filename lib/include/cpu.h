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
#include "debug.h"

/* Flag accessors */
#define ZF (uint8_t)((ctx->cpu.regs.f & 0x4) >> 3)
#define NF (uint8_t)((ctx->cpu.regs.f & 0x3) >> 2)
#define HF (uint8_t)((ctx->cpu.regs.f & 0x2) >> 1)
#define CF (uint8_t)(ctx->cpu.regs.f & 0x1)

/* Readability macro for unset flags */
#define NOT_SET 0

/*
 * @brief Set Z, N, H, and C flags in a single
 * macro
 *
 * @param z zero flag
 * @param n subtract flag
 * @param h half carry flag
 * @param c carry flag
 */
#define CPU_SET_FLAGS(z, n, h, c)      \
    do {                               \
        ctx->cpu.regs.f |= (z << 0x3); \
        ctx->cpu.regs.f |= (n << 0x2); \
        ctx->cpu.regs.f |= (h << 0x1); \
        ctx->cpu.regs.f |= c;          \
    } while (0);

#define FETCH_AND_SET_WORD(val) \
    do {                              \
        fetch_imm(ctx);               \
        val = (ctx->cpu.cbyte);      \
                                      \
        fetch_imm(ctx);               \
        val |= (ctx->cpu.cbyte << 8);  \
    } while (0);

/*
 * @brief Callback locked macro for manipulating 8-bit 
 * registers
 *
 * @param reg register to access
 */
#define REG(reg) ctx->cpu.regs.reg

/*
 * @brief Callback locked macro for manipulating word-sized 
 * registers
 *
 * @param high 8-bit register
 * @param low 8-bit register
 */
#define REGWORD(high, low) (REG(high) << 8) | (REG(low))

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
    printf("-------------------\n");
    printf("| General Purpose |\n");
    printf("-------------------\n");
    printf("A = %x\nF = %x\nB = %x\nC = %x\nD = %x\nE = %x\nH = %x\nL = %x\n\n",
           a, f, b, c, d, e, h, l);

    /* Dispay word-sized 'special' registers */
    printf("-------------------\n");
    printf("|     Special     |\n");
    printf("-------------------\n");
    printf("SP=0x%x\nPC=0x%x\n\n", sp, pc);

    /* Dispay CPU flags */
    printf("-------------------\n");
    printf("|      Flags      |\n");
    printf("-------------------\n");
    printf("ZF=%x, NF=%x, HF=%x, CF=%x\n\n", ZF, NF, HF, CF);
}

/* Define core cpu functions */
void cycle(context_t* ctx);
void cycle_strict(context_t* ctx, uint64_t cycles);
void begin(context_t* ctx);

/* Define CPU instruction callbacks */
callback_t __nop(context_t* ctx);
callback_t __stop(context_t* ctx);
callback_t __sbc_a_imm8(context_t* ctx);
callback_t __call_zf_p16(context_t* ctx);
callback_t __call_imm16(context_t* ctx);
callback_t __ret_nc(context_t* ctx);
callback_t __or_a_b(context_t* ctx);
callback_t __jp_p16(context_t* ctx);
callback_t __jp_hl(context_t* ctx);
callback_t __ld_h_phl(context_t* ctx);
callback_t __ld_bc_imm16(context_t* ctx);
callback_t __ld_sp_imm16(context_t* ctx);
callback_t __ld_pbc_a(context_t* ctx);
callback_t __inc_bc(context_t* ctx);
callback_t __ei(context_t* ctx);
callback_t __di(context_t* ctx);
callback_t __inc_a(context_t* ctx);
callback_t __dec_b(context_t* ctx);

/* No implementation placeholder */
static inline callback_t __no_impl(context_t* ctx) 
{ 
    /* Dump the unimplemented opcode */
    printf("Opcode 0x%x not implemented!\n", ctx->cpu.opcode);

    /* Dump out registers */
    register_dump(ctx);

    /* Teardown gabe gracefully */
    teardown(2); 
}

/* Instruction callback lookup table */
__attribute__((used)) static callback_fp_t callbacks[256] = {
    [0x00] = __nop,
    [0x01] = __ld_bc_imm16,
    [0x02] = __no_impl,
    [0x03] = __no_impl,
    [0x04] = __no_impl,
    [0x05] = __dec_b,
    [0x06] = __no_impl,
    [0x07] = __no_impl,
    [0x08] = __no_impl,
    [0x09] = __no_impl,
    [0x0a] = __no_impl,
    [0x0b] = __no_impl,
    [0x0c] = __no_impl,
    [0x0d] = __no_impl,
    [0x0e] = __no_impl,
    [0x0f] = __no_impl,
    [0x10] = __stop,
    [0x11] = __no_impl,
    [0x12] = __no_impl,
    [0x13] = __no_impl,
    [0x14] = __no_impl,
    [0x15] = __no_impl,
    [0x16] = __no_impl,
    [0x17] = __no_impl,
    [0x18] = __no_impl,
    [0x19] = __no_impl,
    [0x1a] = __no_impl,
    [0x1b] = __no_impl,
    [0x1c] = __no_impl,
    [0x1d] = __no_impl,
    [0x1e] = __no_impl,
    [0x1f] = __no_impl,
    [0x20] = __no_impl,
    [0x21] = __no_impl,
    [0x22] = __no_impl,
    [0x23] = __no_impl,
    [0x24] = __no_impl,
    [0x25] = __no_impl,
    [0x26] = __no_impl,
    [0x27] = __no_impl,
    [0x28] = __no_impl,
    [0x29] = __no_impl,
    [0x2a] = __no_impl,
    [0x2b] = __no_impl,
    [0x2c] = __no_impl,
    [0x2d] = __no_impl,
    [0x2e] = __no_impl,
    [0x2f] = __no_impl,
    [0x30] = __no_impl,
    [0x31] = __ld_sp_imm16,
    [0x32] = __no_impl,
    [0x33] = __no_impl,
    [0x34] = __no_impl,
    [0x35] = __no_impl,
    [0x36] = __no_impl,
    [0x37] = __no_impl,
    [0x38] = __no_impl,
    [0x39] = __no_impl,
    [0x3a] = __no_impl,
    [0x3b] = __no_impl,
    [0x3c] = __no_impl,
    [0x3d] = __no_impl,
    [0x3e] = __no_impl,
    [0x3f] = __no_impl,
    [0x40] = __no_impl,
    [0x41] = __no_impl,
    [0x42] = __no_impl,
    [0x43] = __no_impl,
    [0x44] = __no_impl,
    [0x45] = __no_impl,
    [0x46] = __no_impl,
    [0x47] = __no_impl,
    [0x48] = __no_impl,
    [0x49] = __no_impl,
    [0x4a] = __no_impl,
    [0x4b] = __no_impl,
    [0x4c] = __no_impl,
    [0x4d] = __no_impl,
    [0x4e] = __no_impl,
    [0x4f] = __no_impl,
    [0x50] = __no_impl,
    [0x51] = __no_impl,
    [0x52] = __no_impl,
    [0x53] = __no_impl,
    [0x54] = __no_impl,
    [0x55] = __no_impl,
    [0x56] = __no_impl,
    [0x57] = __no_impl,
    [0x58] = __no_impl,
    [0x59] = __no_impl,
    [0x5a] = __no_impl,
    [0x5b] = __no_impl,
    [0x5c] = __no_impl,
    [0x5d] = __no_impl,
    [0x5e] = __no_impl,
    [0x5f] = __no_impl,
    [0x60] = __no_impl,
    [0x61] = __no_impl,
    [0x62] = __no_impl,
    [0x63] = __no_impl,
    [0x64] = __no_impl,
    [0x65] = __no_impl,
    [0x66] = __ld_h_phl,
    [0x67] = __no_impl,
    [0x68] = __no_impl,
    [0x69] = __no_impl,
    [0x6a] = __no_impl,
    [0x6b] = __no_impl,
    [0x6c] = __no_impl,
    [0x6d] = __no_impl,
    [0x6e] = __no_impl,
    [0x6f] = __no_impl,
    [0x70] = __no_impl,
    [0x71] = __no_impl,
    [0x72] = __no_impl,
    [0x73] = __no_impl,
    [0x74] = __no_impl,
    [0x75] = __no_impl,
    [0x76] = __no_impl,
    [0x77] = __no_impl,
    [0x78] = __no_impl,
    [0x79] = __no_impl,
    [0x7a] = __no_impl,
    [0x7b] = __no_impl,
    [0x7c] = __no_impl,
    [0x7d] = __no_impl,
    [0x7e] = __no_impl,
    [0x7f] = __no_impl,
    [0x80] = __no_impl,
    [0x81] = __no_impl,
    [0x82] = __no_impl,
    [0x83] = __no_impl,
    [0x84] = __no_impl,
    [0x85] = __no_impl,
    [0x86] = __no_impl,
    [0x87] = __no_impl,
    [0x88] = __no_impl,
    [0x89] = __no_impl,
    [0x8a] = __no_impl,
    [0x8b] = __no_impl,
    [0x8c] = __no_impl,
    [0x8d] = __no_impl,
    [0x8e] = __no_impl,
    [0x8f] = __no_impl,
    [0x90] = __no_impl,
    [0x91] = __no_impl,
    [0x92] = __no_impl,
    [0x93] = __no_impl,
    [0x94] = __no_impl,
    [0x95] = __no_impl,
    [0x96] = __no_impl,
    [0x97] = __no_impl,
    [0x98] = __no_impl,
    [0x99] = __no_impl,
    [0x9a] = __no_impl,
    [0x9b] = __no_impl,
    [0x9c] = __no_impl,
    [0x9d] = __no_impl,
    [0x9e] = __no_impl,
    [0x9f] = __no_impl,
    [0xa0] = __no_impl,
    [0xa1] = __no_impl,
    [0xa2] = __no_impl,
    [0xa3] = __no_impl,
    [0xa4] = __no_impl,
    [0xa5] = __no_impl,
    [0xa6] = __no_impl,
    [0xa7] = __no_impl,
    [0xa8] = __no_impl,
    [0xa9] = __no_impl,
    [0xaa] = __no_impl,
    [0xab] = __no_impl,
    [0xac] = __no_impl,
    [0xad] = __no_impl,
    [0xae] = __no_impl,
    [0xaf] = __no_impl,
    [0xb0] = __or_a_b,
    [0xb1] = __no_impl,
    [0xb2] = __no_impl,
    [0xb3] = __no_impl,
    [0xb4] = __no_impl,
    [0xb5] = __no_impl,
    [0xb6] = __no_impl,
    [0xb7] = __no_impl,
    [0xb8] = __no_impl,
    [0xb9] = __no_impl,
    [0xba] = __no_impl,
    [0xbb] = __no_impl,
    [0xbc] = __no_impl,
    [0xbd] = __no_impl,
    [0xbe] = __no_impl,
    [0xbf] = __no_impl,
    [0xc0] = __no_impl,
    [0xc1] = __no_impl,
    [0xc2] = __no_impl,
    [0xc3] = __jp_p16,
    [0xc4] = __no_impl,
    [0xc5] = __no_impl,
    [0xc6] = __no_impl,
    [0xc7] = __no_impl,
    [0xc8] = __no_impl,
    [0xc9] = __no_impl,
    [0xca] = __no_impl,
    [0xcb] = __no_impl,
    [0xcc] = __call_zf_p16,
    [0xcd] = __call_imm16,
    [0xce] = __no_impl,
    [0xcf] = __no_impl,
    [0xd0] = __ret_nc,
    [0xd1] = __no_impl,
    [0xd2] = __no_impl,
    [0xd3] = __no_impl,
    [0xd4] = __no_impl,
    [0xd5] = __no_impl,
    [0xd6] = __no_impl,
    [0xd7] = __no_impl,
    [0xd8] = __no_impl,
    [0xd9] = __no_impl,
    [0xda] = __no_impl,
    [0xdb] = __no_impl,
    [0xdc] = __no_impl,
    [0xdd] = __no_impl,
    [0xde] = __sbc_a_imm8,
    [0xdf] = __no_impl,
    [0xe0] = __no_impl,
    [0xe1] = __no_impl,
    [0xe2] = __no_impl,
    [0xe3] = __no_impl,
    [0xe4] = __no_impl,
    [0xe5] = __no_impl,
    [0xe6] = __no_impl,
    [0xe7] = __no_impl,
    [0xe8] = __no_impl,
    [0xe9] = __jp_hl,
    [0xea] = __no_impl,
    [0xeb] = __no_impl,
    [0xec] = __no_impl,
    [0xed] = __no_impl,
    [0xee] = __no_impl,
    [0xef] = __no_impl,
    [0xf0] = __no_impl,
    [0xf1] = __no_impl,
    [0xf2] = __no_impl,
    [0xf3] = __di,
    [0xf4] = __no_impl,
    [0xf5] = __no_impl,
    [0xf6] = __no_impl,
    [0xf7] = __no_impl,
    [0xf8] = __no_impl,
    [0xf9] = __no_impl,
    [0xfa] = __no_impl,
    [0xfb] = __ei,
    [0xfc] = __no_impl,
    [0xfd] = __no_impl,
    [0xfe] = __no_impl,
    [0xff] = __no_impl,
};
