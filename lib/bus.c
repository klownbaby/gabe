/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "bus.h"
#include "utils.h"

/*
 * @brief Maps address to device/memory region
 * from emulated bus, and returns a byte
 *
 * @param addr The mapped address
 */
uint8_t bus_read(context_t* ctx, uint16_t addr)
{
    uint8_t byte = 0x0;

    if (addr <= CART_MEM_OFFSET)
    {
        byte = ctx->rom[addr];
        GOTO_SUCCESS;
    }

success:
    return byte;
}

/*
 * @brief Maps address to device/memory region
 * from emulated bus and writes byte to location
 *
 * @param addr The mapped address to write to
 */
void bus_write(context_t* ctx, uint16_t addr, uint8_t byte)
{
    if (addr <= CART_MEM_OFFSET)
    {
        /* write the fucking byte */
        ctx->rom[addr] = byte;
        GOTO_SUCCESS;
    }

success:
    return;
}
