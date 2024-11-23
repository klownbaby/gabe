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

/* Push handlers */
void pushb(context_t* ctx, uint8_t byte);
void pushw(context_t* ctx, uint16_t word);

/* Pop handlers */
uint8_t popb(context_t* ctx);
uint16_t popw(context_t* ctx);
