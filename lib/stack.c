#include "stack.h"
#include "cpu.h"

/*
 * @brief Push a byte onto the stack
 *
 * @param ctx Emulator context
 * @param byte byte to push onto the stack
 */
void pushb(context_t* ctx, uint8_t byte)
{
    /* Set current stack pointer to byte and decrement */
    ctx->cpu.stack[REG(sp)--] = byte;
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
    ctx->cpu.stack[REG(sp)--] = (word & 0xF0);

    /* Set MSB to current stack pointer and decrement */
    ctx->cpu.stack[REG(sp)--] = (word & 0x0F);
}

/*
 * @brief Pop a byte from the top of the stack
 *
 * @param ctx Emulator context
 */
uint8_t popb(context_t* ctx)
{
    /* Get the current byte at SP and increment */
    return ctx->cpu.stack[REG(sp++)];
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
    value = ctx->cpu.stack[REG(sp++)];

    /* Get the MSB of the word and increment */
    value |= (ctx->cpu.stack[REG(sp++)] << 8);

    /* Return the full word-sized value */
    return value;
}
