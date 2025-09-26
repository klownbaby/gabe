/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "emulator.h"

/*
 * @brief Push a byte onto the stack
 *
 * @param ctx Emulator context
 * @param byte byte to push onto the stack
 */
void pushb(context_t* ctx, uint8_t byte)
{
    /* Set current stack pointer to byte and decrement */
    bus_write(ctx, REG(sp--), byte);
}

/*
 * @brief Push a word on to the stack
 *
 * @param ctx Emulator context
 * @param word word to push onto the stack
 */
void pushw(context_t* ctx, uint16_t word)
{
    /* Set LSB to current stack pointer and decrement */
    bus_write(ctx, REG(sp--), ((word & 0xFF00) >> 8));

    /* Set MSB to current stack pointer and decrement */
    bus_write(ctx, REG(sp--), (word & 0x00FF));
}

/*
 * @brief Pop a byte from the top of the stack
 *
 * @param ctx Emulator context
 */
uint8_t popb(context_t* ctx)
{
    /* Get the current byte at SP and increment */
    return bus_read(ctx, ++REG(sp));
}

/*
 * @brief Pop a word from the top of the stack
 *
 * @param ctx Emulator context
 */
uint16_t popw(context_t* ctx)
{
    uint16_t value = 0;

    /* Get the LSB of the word and increment */
    value = bus_read(ctx, ++REG(sp));

    /* Get the MSB of the word and increment */
    value |= (bus_read(ctx, ++REG(sp)) << 8);

    /* Return the full word-sized value */
    return value;
}
