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

#define CHECKSUM_START 0x0134
#define CHECKSUM_END   0x014C

#define MAP_NLIC(header)
#define MAP_LIC(header)

#define MAP_CART_TYPE(header)

#define MAP_ROM_SIZE(header)
#define MAP_RAM_SIZE(header)

#define SHOW_CART_INFO(header) \
    do {                                         \
        printf("\n!!!Cartridge Info!!!\n");      \
        printf("Title: %s\n", header->title);    \
        printf("New licensee code: %s\n",        \
               MAP_NLIC(header));                \
        printf("Cartridge type: %s\n",           \
               MAP_CART_TYPE(header));           \
        printf("ROM size: %d\n",                 \
               MAP_ROM_SIZE(header));            \
        printf("RAM size: %d\n",                 \
               MAP_RAM_SIZE(header));            \
    } while(0)


void read_cart_info(char* filename, cart_header_t* buf);
