/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdio.h>
#include "cpu.h"

/*
 * @brief Prints out values of all CPU registers
 *
 * @param ctx Emulator context
 */
OPTIONAL static void register_dump(context_t* ctx)
{
    GET_REGS(ctx);

    /* Display general purpose registers */
    printf("\n---REGISTER DUMP---\n");
    printf("-------------------\n");
    printf("| General Purpose |\n");
    printf("-------------------\n");
    printf("A=%x\nF=%x\nB=%x\nC=%x\nD=%x\nE=%x\nH=%x\nL=%x\n",
           a, f, b, c, d, e, h, l);

    /* Dispay word-sized 'special' registers */
    printf("-------------------\n");
    printf("|     Special     |\n");
    printf("-------------------\n");
    printf("SP=0x%x\nPC=0x%x\n", sp, pc);
}

/*
 * @brief NOP instruction for Z80 CPU
 * increments program counter
 *
 * @param ctx Emulator context
 */
callback_t nop(context_t* ctx)
{
    /* 
     * NOP instruction, we just want to increment the
     * program counter, nothing else 
     */
    INC_PC;
}
