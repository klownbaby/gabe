/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdint.h>

/* Debug flags */
#define DEBUG
#define SINGLE_STEP

/* Flag to use static allocations for memory map, instead of allocating heap */
#define STATIC_ALLOCS

/* Define common size constants */
#define _16K 0x3FFF
#define _8K  0x1FFF
#define _4K  0xFFF
