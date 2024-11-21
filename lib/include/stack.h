#pragma once

#include "types.h"

/* Push handlers */
void pushb(context_t* ctx, uint8_t byte);
void pushw(context_t* ctx, uint16_t word);

/* Pop handlers */
uint8_t popb(context_t* ctx);
uint16_t popw(context_t* ctx);
