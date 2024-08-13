/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "bus.h"

/*
 * @brief Maps address to device/memory region
 * from emulated bus, and returns value
 *
 * @param addr The mapped address
 */
uint8_t* bus_read(uint8_t* addr)
{
    return 0x0;
}

/*
 * @brief Maps address to device/memory region
 * from emulated bus and writes value to location
 *
 * @param addr The mapped address to write to
 */
void bus_write(uint8_t* addr)
{
}
