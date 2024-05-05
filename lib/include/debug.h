/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <unistd.h>

#define INFO    0
#define ERRO    1
#define WARN    2
#define VERB    3

#define RED     printf("\033[1;31m")
#define GREEN   printf("\033[1;32m")
#define YELLOW  printf("\033[1;33m")
#define RESET   printf("\033[0m")

#define DBG_MSG(level, s)        \
    do {                         \
        switch(level) {          \
        case INFO:               \
            printf("[ INFO ]    %s\n", s);   \
            break;               \
        case ERRO:                \
            RED;                 \
            printf("[ ERRO ]    %s\n", s);   \
            RESET;               \
            break;               \
        case WARN:               \
            YELLOW;              \
            printf("[ WARN ]    %s\n", s);   \
            RESET;               \
            break;               \
        case VERB:            \
            printf("[ VERB ]    %s\n", s);   \
            break;               \
        }                        \
    } while (0);
