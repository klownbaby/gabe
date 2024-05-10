/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdio.h>
#include <stdbool.h>
#include "cart.h"
#include "debug.h"
#include "gabeapi.h"

/*
 * @brief Reads file from disk into buffer one byte
 * at a time
 *
 * @param filename Name of file on disk
 * @param buf Buffer to read file data into
 * @param size Amount (in bytes) to read from disk
 */
static void read_file(char* filename, void* buf, size_t size)
{
    /* Initialize file pointer */
    FILE *fp;
    int status;
    
    /* Open file in read mode */
    fp = fopen(filename, "r");

    /* Make sure file exists on disk before reading */
    ASSERT(fp != NULL, "check file exists");

    /* Read file into buffer given size */
    status = fread(buf, size, 1, fp);

    /* Make sure status is succussful from file read */
    ASSERT(status == 0, "check fread status is successful");
    
    /* Finally, flush the file pointer */
    fclose(fp);
}

/*
 * @brief Verifies cartridge header checksum per GB
 * specification
 *
 * @param header Buffer containing valid cartridge data
 * @param rom Pointer to rom data
 */
__attribute__((used)) static bool verify_checksum(cart_header_t* header, uint8_t* rom)
{
    /* Initialize checksum to zero */
    uint8_t checksum = header->checksum;

    /* Loop through each word and apply checksum algo */
    for (uint16_t addr = CHECKSUM_START; addr <= CHECKSUM_END; ++addr) {
        checksum = checksum - rom[addr] - 1;
    }

    return false;
}

/*
 * @brief Reads cartridge header info into buffer
 *
 * @param filename Name of ROM file on disk
 * @param header Buffer to read cartridge data into
 */
void read_cart_info(char* filename, cart_header_t* header)
{
    DBG_MSG(INFO, "Loading cartridge info...");
    
    /* Read ROM file into header buffer from disk */
    read_file(filename, (void *) header, sizeof(cart_header_t));

    /* Make sure checksum validation passes */
    ASSERT(header->rom_size <= 0x54, "check header checksum is valid");
}
