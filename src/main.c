/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#include "libgabe.h"

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
int main()
{
    /* 
     * This  will initialize all emulated hardware, assuming 
     * a cartridge is loaded.
     *
     * So make sure to load one...
     */
    __gabe_start();

    return 0;
}
