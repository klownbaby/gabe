/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

 #include "emulator.h"

/* Initialize static global emulator context */
context_t ctx;

/*
 * @brief Allocates necessary memory for ROM/RAM
 * banks on the gameboy
 *
 * @param *ctx Pointer to context object
 */
static void ctxalloc(context_t* ctx)
{
#ifdef STATIC_ALLOCS
    /* Create memory map */
    ctx->rom = __rb16;
    ctx->vram = __vram;
    ctx->exram = __extram;
    ctx->echram = __echo;
    ctx->wram = __wram;
    ctx->io = __io_reg;
#else
#endif /* STATIC_ALLOCS */
}

/*
 * @brief Properly frees any memory allocated by emulator
 * context
 *
 * @param *ctx Pointer to context object
 */
static void ctxfree(context_t* ctx)
{
#ifdef STATIC_ALLOCS
#else
    /* Free cartridge ROM allocation */
    free(ctx->rom);

    /* Free video RAM allocation */
    free(ctx->vram);

    /* Free external RAM allocation */
    free(ctx->exram);

    /* Free echo RAM on allocation */
    free(ctx->echram);

    /* Free work RAM on allocation */ 
    free(ctx->wram);

    /* Set running state to false */
    ctx->running = false;
#endif /* STATIC_ALLOCS */
}

/*
 * @brief Sets up emulator hardware context
 *
 * @param *ctx Pointer to context object
 */
static void ctxinit(context_t* ctx)
{
    /* Create memory map */
    ctxalloc(ctx);

    /* Set state to running */
    ctx->running = true;
    ctx->cpu.regs.pc = ROM_ENTRY;
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

    ASSERT(ctx.running);

    /* Begin execution */
    while(ctx.running) cycle(&ctx);

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
