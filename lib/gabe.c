/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdio.h>
#include "debug.h"

/*
 * @brief This will initialize all emulated hardware,
 * assuming a cartridge is loaded.
 *
 * So make sure to load one...
 */
void __gabe_start()
{
    printf("Starting gabe...\n\n");

    ASSERT(1 == 2, "check one is one");

    DBG_MSG(INFO, "Info test");
}

