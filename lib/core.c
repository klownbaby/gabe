/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdlib.h>
#include "debug.h"
#include "cart.h"
#include "core.h"
#include "cpu.h"

/* Initialize static global emulator context */
static context_t ctx;

/*
 * @brief Sets up emulator hardware context
 *
 * @param *ctx Pointer to context object
 */
static void ctxinit(context_t* ctx)
{
    ctx->running = true;
    ctx->cpu.regs.pc = ROM_ENTRY;
}

/*
 * @brief Properly frees any memory allocated by emulator
 * context
 *
 * @param *ctx Pointer to context object
 */
static void ctxfree(context_t* ctx)
{
    free(ctx->rom);

    ctx->running = false;
}

/*
 * @brief This will initialize all emulated hardware,
 * assuming a cartridge is loaded.
 *
 * So make sure to load one...
 */
void gabeinit(char* romfile)
{
    DBG_MSG(INFO, "Starting gabe...");

    /* Set context to default state */
    ctxinit(&ctx);
    /* Load cartridge */
    load_cart(&ctx, romfile);

    /* Begin execution */
    cycle_strict(&ctx, 10);

    ASSERT(ctx.running, "Context initialized properly");

    register_dump(&ctx);
}

/*
 * @brief Teardown and cleanup any dangling pointers
 * and gracefully exit
 *
 * @param status Exit status of gabe
 */
void teardown(uint8_t status)
{
    DBG_MSG(INFO, "Exiting gabe... ");

    /* Free any danlging pointers */
    ctxfree(&ctx);

    /* Finally, exit gracefully */
    exit(status);
}
