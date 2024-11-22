/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdio.h>
#include "bus.h"
#include "utils.h"
#include "debug.h"

/*
 * @brief Maps address to device/memory region
 * from emulated bus, and returns a byte
 *
 * @param addr The mapped address
 */
uint8_t bus_read(context_t* ctx, uint16_t addr)
{
    uint8_t byte = 0;

    if (addr < MEM_ROM_BANK_END)
    {
        byte = ctx->rom[addr];
        GOTO_SUCCESS;
    } 
    else if (addr < MEM_VRAM_END) 
    {
        byte = ctx->vram[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_EXRAM_END) 
    {
        byte = ctx->exram[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_END) 
    {
        byte = ctx->wram[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_BANK_END) 
    {
        /* TODO */
        byte = ctx->wram[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_ECHRAM_END) 
    {
        byte = ctx->echram[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_OAM_END) 
    {
        byte = ctx->oam[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_UNUSABLE_END) 
    {
        GOTO_FAIL;
    }
    else if (addr < MEM_IOREG_END) 
    {
        byte = ctx->io[addr];
        GOTO_SUCCESS;
    }
    else if (addr < MEM_HRAM_END) 
    {
        byte = ctx->hram[addr];
        GOTO_SUCCESS;
    }

fail:
    /* TODO Handle failures in a better way */
    DBG_MSG(ERRO, "Bus read error!");

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
    if (addr < MEM_ROM_BANK_END)
    {
        ctx->rom[addr] = byte;
        GOTO_SUCCESS;
    } 
    else if (addr < MEM_VRAM_END) 
    {
        ctx->vram[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_EXRAM_END) 
    {
        ctx->exram[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_END) 
    {
        ctx->wram[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_BANK_END) 
    {
        /* TODO */
        ctx->wram[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_ECHRAM_END) 
    {
        ctx->echram[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_OAM_END) 
    {
        ctx->oam[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_UNUSABLE_END) 
    {
        GOTO_FAIL;
    }
    else if (addr < MEM_IOREG_END) 
    {
        ctx->io[addr] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_HRAM_END) 
    {
        ctx->hram[addr] = byte;
        GOTO_SUCCESS;
    }

fail:
    /* TODO Handle failures in a better way */
    DBG_MSG(ERRO, "Bus write error!");

success:
    return;

}
