/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include "core.h"

/* Levels of debug messages */
#define INFO    0
#define ERRO    1
#define WARN    2
#define VERB    3

/* Color definitions for printing messages */
#define RED     printf("\033[1;31m")
#define GREEN   printf("\033[1;32m")
#define YELLOW  printf("\033[1;33m")
#define RESET   printf("\033[0m")

#ifdef DEBUG
/*
 * @brief Prints debug level message to console
 *
 * @param level Level at which to print (INFO, ERRO, WARN)
 * @param s     String to log with leader
 */
#define DBG_MSG(level, ...)      \
    do {                         \
        switch(level) {          \
        case INFO:               \
            printf("[ INFO ]    "); \
            printf(__VA_ARGS__); \
            printf("\n");        \
            break;               \
        case ERRO:               \
            RED;                 \
            printf("[ ERRO ]    "); \
            printf(__VA_ARGS__); \
            printf("\n");        \
            RESET;               \
            break;               \
        case WARN:               \
            YELLOW;              \
            printf("[ WARN ]    "); \
            printf(__VA_ARGS__); \
            printf("\n");        \
            RESET;               \
            break;               \
        case VERB:               \
            printf("[ VERB ]    "); \
            printf(__VA_ARGS__); \
            printf("\n");        \
            break;               \
        }                        \
    } while (0)

#else /* NOP out DBG_MSG if not in debug mode */
#define DBG_MSG(level, ...)
#endif /* DBG */

/*
 * @brief Used for runtime assertions, not unit tests
 *
 * @param cond Condition to assert TRUE
 * @param s    String to log on assertion pass/fail
 */
#define ASSERT(cond)             \
    do {                         \
        if (!(cond)) {           \
            RED;                 \
            printf("[ FAIL ]    Failed assertion! "#cond); \
            RESET;               \
            teardown(1);         \
        }                        \
    } while (0)

/*
 * @brief Step into an opcode and wait for input
 */
#define STEP \
    printf("=> %x\t", ctx->cpu.opcode); getchar();
