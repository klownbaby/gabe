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

