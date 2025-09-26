/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "cpu.h"
#include "emulator.h"

/* No implementation placeholder */
callback_t __no_impl(context_t* ctx) 
{ 
    /* Dump the unimplemented opcode */
    DBG_MSG(ERRO, "Opcode %x not implemented!", ctx->cpu.opcode);

    /* Dump out registers */
    register_dump(ctx);

    /* Teardown gabe gracefully */
    teardown(2); 
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
 * @brief Prefix instruction for next opcode
 *
 * @param ctx Emulator context
 */
callback_t __prefix(context_t* ctx)
{
    /* Fetch the next byte and increment PC */
    FETCH_IMM;

    /* Get associated prefixed callback */
    LOOKUP_PREFIX_CALLBACK(ctx->cpu.cbyte, ctx);
}

/*
 * @brief CPU enter low power mode
 * 
 * This is a 2 byte instruction so
 * we must increment the program
 * counter once more
 *
 * @param ctx Emulator context
 */
callback_t __stop(context_t* ctx)
{
    INC_PC;
}

/*
 * @brief subtract with carry immediate
 * 8 bit value from register A
 *
 * @param ctx Emulator context
 */
callback_t __sbc_a_imm8(context_t* ctx)
{
    uint8_t value = 0;

    /* Fetch the next byte and increment PC */
    FETCH_IMM;

    /* Dereference the current byte */
    value = ctx->cpu.cbyte + CF;

    /* Set flags accordingly */
    CPU_SET_FLAGS(
        REG(a) - value == 0,
        1,
        ((REG(a) & 0xF) - ((ctx->cpu.cbyte & 0xF) - CF) < 0),
        (REG(a) - (ctx->cpu.cbyte & 0xF) < 0));

    /* Finally, set the value of the A register */
    REG(a) -= value + CF;
}

/*
 * @brief Call subroutine at 16-bit address
 * if ZF is set
 *
 * @param ctx Emulator context
 */
callback_t __call_zf_p16(context_t* ctx)
{
    uint16_t addr = 0;

    /* Check that zero flag is enabled before calling */
    if (ZF)
    {
        /* Fetch word from memory and store in target address */
        FETCH_AND_SET_WORD(addr);

        /* Finally, jump to callee and align stack */
        CALL(addr);
    }
}

/*
 * @brief Call subroutine at 16-bit immediate address
 *
 * @param ctx Emulator context
 */
callback_t __call_imm16(context_t* ctx)
{
    uint16_t addr = 0;

    /* Fetch word from memory and store in target address */
    FETCH_AND_SET_WORD(addr);

    /* Finally, jump to callee and align stack */
    CALL(addr);
}

/*
 * @brief Return from subroutine if ZF
 * is set
 *
 * @param ctx Emulator context
 */
callback_t __ret_z(context_t* ctx)
{
    /* Check that carry flag is enabled before returning */
    if (ZF)
    {
        /* Pop return address from top of stack and goto */
        REG(pc) = popw(ctx);
    }
}

/*
 * @brief Return from subroutine if CF
 * is not set
 *
 * @param ctx Emulator context
 */
callback_t __ret_nc(context_t* ctx)
{
    /* Check that carry flag is enabled before returning */
    if (!CF)
    {
        /* Pop return address from top of stack and goto */
        REG(pc) = popw(ctx);
    }
}

/*
 * @brief Bitwise OR register A with register B
 *
 * @param ctx Emulator context
 */
callback_t __or_a_b(context_t* ctx)
{
    /* OR register A and B and store result in register A */
    REG(a) |= REG(b);

    /* Set zero flag if value is zero, reset all other flags */
    CPU_SET_FLAGS(REG(a) == 0, 0, 0, 0);
}

/*
 * @brief Jump to 16 bit address
 *
 * @param ctx Emulator context
 */
callback_t __jp_p16(context_t* ctx)
{
    uint16_t addr = 0;

    /* Fetch word from memory and store in target address */
    FETCH_AND_SET_WORD(addr);

    /* Finally, jump to address (account for auto PC increment) */
    REG(pc) = addr - 1;
}

/*
 * @brief Jump to 16 bit address stored in
 * HL register
 *
 * @param ctx Emulator context
 */
callback_t __jp_hl(context_t* ctx)
{
    /* Jump to address stored in HL register */
    REG(pc) = REGWORD(h, l);
}

/*
 * @brief Set stack pointer to a 16 bit
 * immediate address
 *
 * @param ctx Emulator context
 */
callback_t __ld_sp_imm16(context_t* ctx)
{
    uint16_t addr = 0;
    
    /* Fetch word from memory and store in target address */
    FETCH_AND_SET_WORD(addr);

    /* Finally, set the stack pointer to the new address */
    REG(sp) = addr;
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
    FETCH_IMM;
    REG(c) = ctx->cpu.cbyte;

    /* Little endian so set LSB to B reg */
    FETCH_IMM;
    REG(b) = ctx->cpu.cbyte;
}

/*
 * @brief Load the register H with
 * the byte pointed to at register HL
 *
 * @param ctx Emulator context
 */
callback_t __ld_h_phl(context_t* ctx)
{
    /* Get the pointer stored in HL register */
    uint16_t phl = REGWORD(h, l);

    /* Dereference byte at phl */
    REG(h) = ctx->rom[phl];
}

/*
 * @brief Load the register H with
 * the byte pointed to at register HL
 *
 * @param ctx Emulator context
 */
callback_t __ld_hl_imm16(context_t* ctx)
{
    /* Little endian so set MSB to L reg */
    FETCH_IMM;
    REG(l) = ctx->cpu.cbyte;

    /* Little endian so set LSB to H reg */
    FETCH_IMM;
    REG(h) = ctx->cpu.cbyte;
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
 * @brief Enable interrupts
 *
 * @param ctx Emulator context
 */
callback_t __ei(context_t* ctx)
{
    ctx->interrupt_enable = 1;
}

/*
 * @brief Disable interrupts
 *
 * @param ctx Emulator context
 */
callback_t __di(context_t* ctx)
{
    ctx->interrupt_enable = 0;
}

/*
 * @brief Increment A register
 *
 * @param ctx Emulator context
 */
callback_t __inc_a(context_t* ctx)
{
    /* Increment A register */
    ++REG(a);

    /* Set flags accordingly */
    CPU_SET_FLAGS(
        REG(a) == 0,
        0,
        (REG(a) & 0xF),
        NOT_SET);
}

/*
 * @brief Decrement B register
 *
 * @param ctx Emulator context
 */
callback_t __dec_b(context_t* ctx)
{
    /* Decrement B register */
    --REG(b);

    /* Set flags accordingly */
    CPU_SET_FLAGS(
        REG(b) == 0,
        1,
        (REG(b) & 0xF) == 0xF,
        NOT_SET);
}
