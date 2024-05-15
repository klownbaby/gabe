/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include <stdio.h>
#include <stdlib.h>
#include "gabe.h"

/*
 * This is intended to be the "frontend" layer for gabe.
 * Compile and link the gabe static lib (this is done for
 * you in this implementation) to any target "frontend"
 * which could be any arbitrary UI or interface you wish.
 *
 * The exact implementation is up to you, this is merely
 * an overly-verbose example.
 * 
 * See libgabe docs for more info (if I have gotten around
 * to writing them yet lol).
 */
int main(int argc, char** argv)
{
    if (argc < 2)
    {
        printf("ROM file required!\n");
        exit(1);
    }

    /* Get rom file name from args */
    char* romfile = argv[1];

    /* Init and teardown */
    gabeinit(romfile);
    teardown(0);
}
