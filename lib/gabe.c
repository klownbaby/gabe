/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "debug.h"
#include "types.h"
#include "lgabe.h"
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
void gabeinit()
{
    printf("\nStarting gabe...\n\n");

    /* Set context to default state */
    ctxinit(&ctx);

    ASSERT(ctx.running, "check context initialized properly");
}


/*
 * @brief Teardown and cleanup any dangling pointers
 * and gracefully exit
 *
 * @param status Exit status of gabe
 */
void teardown(uint8_t status)
{
    printf("\nExiting gabe... ");

    /* Free any danlging pointers */
    ctxfree(&ctx);

    printf("done\n");

    /* Finally, exit gracefully */
    exit(status);
}
