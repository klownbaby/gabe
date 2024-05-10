/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "debug.h"
#include "gabeapi.h"

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
}

/*
 * @brief Properly frees any memory allocated by emulator
 * context
 *
 * @param *ctx Pointer to context object
 */
static void ctxfree(context_t* ctx)
{
    ctx->running = false;
}

/*
 * @brief This will initialize all emulated hardware,
 * assuming a cartridge is loaded.
 *
 * So make sure to load one...
 */
GABE_API void gabeinit()
{
    DBG_MSG(INFO, "Starting gabe...");

    /* Set context to default state */
    ctxinit(&ctx);

    /* Read header info from ROM */
    read_cart_info("test.rom", &ctx.header);

    ASSERT(ctx.running, "check context initialized properly");
}

/*
 * @brief Teardown and cleanup any dangling pointers
 * and gracefully exit
 *
 * @param status Exit status of gabe
 */
GABE_API void teardown(uint8_t status)
{
    DBG_MSG(INFO, "Exiting gabe... ");

    /* Free any danlging pointers */
    ctxfree(&ctx);

    /* Finally, exit gracefully */
    exit(status);
}
