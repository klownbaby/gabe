#pragma once

#include "types.h"

/* Push handlers */
void pushb(context_t* ctx, uint8_t byte);
void pushw(context_t* ctx, uint16_t word);

/* Pop handlers */
void popb(context_t* ctx, uint8_t byte);
void popw(context_t* ctx, uint16_t word);
