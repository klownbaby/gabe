/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "emulator.h"

/* Test bit 7 in address pointed to by HL */
callback_t __bit_7_phl(context_t* ctx) 
{ 
    uint16_t addr = 0;
    uint8_t byte = 0;

    addr = REGWORD(h, l);
    byte = bus_read(ctx, addr);

    /* Set zero flag accordingly */
    CPU_SET_FLAGS(
        (byte & 0x7),
        NOT_SET,
        NOT_SET,
        NOT_SET);
}

