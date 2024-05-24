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

/*
 * @brief Reads file from disk into buffer one byte
 * at a time
 *
 * @param filename Name of file on disk
 * @param buf Buffer to read file data into
 * @param size Amount (in bytes) to read from disk
 */
static void read_file(
    char* filename,
    void* buf,
    size_t size, 
    size_t offset, 
    uint32_t nItems)
{
    /* Initialize file pointer */
    FILE *fp;
    size_t read;
    
    /* Open file in read mode */
    fp = fopen(filename, "r");

    /* Make sure file exists on disk before reading */
    ASSERT(fp != NULL, "File exists");

    /* Seek to offset from start of file */
    fseek(fp, offset, SEEK_SET);

    /* Read file into buffer given size */
    read = fread(buf, size, nItems, fp);

    printf("read=%lu\n", read);
    printf("size=%lu\n", size);

    /* Make sure status is succussful from file read */
    ASSERT(read != 0, "File read is successful");
    
    /* Make sure to rewind file pointer! */
    rewind(fp);

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
OPTIONAL static bool verify_checksum(cart_header_t* header, uint8_t* rom)
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
void read_cart_header(char* filename, cart_header_t* header)
{
    DBG_MSG(INFO, "Loading cartridge header...");
    
    /* Read ROM file into header buffer from disk */
    read_file(filename, (void *) header, 
              sizeof(cart_header_t), 0x100, 1);

    /* Make sure checksum validation passes */
    ASSERT(header->rom_size <= 0x54, "Header checksum is valid");
}

/*
 * @brief Loads a cartridge (ROM) into emulator context
 *
 * @param ctx Emulator context
 * @param header Valid cartridge header data buffer
 */
void load_cart(context_t* ctx, char* filename)
{
    /* Read header info into buffer */
    read_cart_header(filename, &ctx->header);

    DBG_MSG(INFO, "Loading cartridge...");

    SHOW_CART_INFO(ctx->header);

    /* Read rom file into buffer */
    read_file(filename, (void *) ctx->rom,
              sizeof(uint8_t), 
              0x0, 
              GET_ROM_SIZE(ctx->header.rom_size));

    /* Ensure rom was successfully loaded into buffer */
    ASSERT(ctx->rom != NULL, "ROM pointer is not null");
}
