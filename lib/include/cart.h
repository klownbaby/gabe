/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include "types.h"

/* Define checksum constants */
#define CHECKSUM_START 0x0134
#define CHECKSUM_END   0x014C

#define ROM_ENTRY      0x100

/* Define unkown type (macro) for type mapping */
#define UNKNOWN        "\0"

#define GET_ROM_SIZE(size) (32 << size) * 1000

/* Define mapping for rom types */
__attribute__((used)) static const char* ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    UNKNOWN,
    "MBC2",
    "MBC2+BATTERY",
    UNKNOWN,
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    UNKNOWN,
    UNKNOWN,
    UNKNOWN,
    UNKNOWN,
    UNKNOWN,
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    UNKNOWN,
    "MBC6",
    UNKNOWN,
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

/* Define mapping for license codes */
__attribute__((used)) static const char* LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

/*
 * @brief Dumps the cartridge header info from
 * a cart_header_t struct
 *
 * @param header Buffer containing valid header data
 */
#define SHOW_CART_INFO(header) \
    do {                                       \
        printf("\n--------------------\n");    \
        printf("\n!!!Cartridge Info!!!\n");    \
        printf("\n--------------------\n\n");  \
        printf("\tTitle: %s\n", header.title); \
        printf("\tNew licensee code: %s\n",    \
               LIC_CODE[header.nlic]);         \
        printf("\tCartridge type: %s\n",       \
               ROM_TYPES[header.type]);        \
        printf("\tROM size: %d\n",             \
               GET_ROM_SIZE(header.rom_size)); \
        printf("\tRAM size: %d\n\n",           \
               header.ram_size);               \
    } while(0)


/* Define cartridge load/read functions */
void read_cart_header(char* filename, cart_header_t* buf);
void load_cart(context_t* ctx, char* filename);
