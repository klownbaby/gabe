/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "emulator.h"

/* Initialize bus read statistics array */
static uint64_t bus_read_stats[10] = { 0 };

/* Initialize bus write statistics array */
static uint64_t bus_write_stats[10] = { 0 };

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
        ++bus_read_stats[ROM_STATS_IDX];

        GOTO_SUCCESS;
    } 
    else if (addr < MEM_VRAM_END) 
    {
        byte = ctx->vram[addr & 0xFFF];
        ++bus_read_stats[VRAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_EXRAM_END) 
    {
        byte = ctx->exram[addr & 0xFFF];
        ++bus_read_stats[EXRAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_END) 
    {
        byte = ctx->wram[addr & 0xFFF];
        ++bus_read_stats[WRAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_BANK_END) 
    {
        /* TODO */
        byte = ctx->wram[addr & 0xFFF];
        ++bus_read_stats[WRAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_ECHRAM_END) 
    {
        byte = ctx->echram[addr & 0xFFF];
        ++bus_read_stats[ECHRAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_OAM_END) 
    {
        byte = ctx->oam[addr & 0xFFF];
        ++bus_read_stats[OAM_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_UNUSABLE_END) 
    {
        ++bus_read_stats[UNUSABLE_STATS_IDX];

        GOTO_FAIL;
    }
    else if (addr < MEM_IOREG_END) 
    {
        byte = ctx->io[addr & 0xFF];
        ++bus_read_stats[IOREG_STATS_IDX];

        GOTO_SUCCESS;
    }
    else if (addr < MEM_HRAM_END) 
    {
        byte = ctx->hram[addr & 0xFFF];
        ++bus_read_stats[HRAM_STATS_IDX];

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
        ctx->vram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_EXRAM_END) 
    {
        ctx->exram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_END) 
    {
        ctx->wram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_WRAM_BANK_END) 
    {
        /* TODO */
        ctx->wram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_ECHRAM_END) 
    {
        ctx->echram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_OAM_END) 
    {
        ctx->oam[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_UNUSABLE_END) 
    {
        GOTO_FAIL;
    }
    else if (addr < MEM_IOREG_END) 
    {
        ctx->io[addr & 0xFF] = byte;
        GOTO_SUCCESS;
    }
    else if (addr < MEM_HRAM_END) 
    {
        ctx->hram[addr & 0xFFF] = byte;
        GOTO_SUCCESS;
    }

fail:
    /* TODO Handle failures in a better way */
    DBG_MSG(ERRO, "Bus write error!");

success:
    return;

}
