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

void __gabe_start()
{
    printf("Starting gabe...\n\n");

    DBG_MSG(INFO, "Info test")
    DBG_MSG(ERRO, "Error test")
    DBG_MSG(WARN, "Warn test")
}


