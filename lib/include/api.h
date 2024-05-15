/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <stdint.h>
#include "types.h"

/* Most likely will full implment this later */
#define GABE_API __attribute__((used))

/* Define all API calls */
GABE_API void gabeinit(char* romfile);
GABE_API void teardown(uint8_t status);

GABE_API cart_header_t* read_cart_header();
