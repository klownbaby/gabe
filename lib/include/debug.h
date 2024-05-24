/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

#include <stdio.h>
#include <unistd.h>
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

/*
 * @brief Used for runtime assertions, not unit tests
 *
 * @param cond Condition to assert TRUE
 * @param s    String to log on assertion pass/fail
 */
#define ASSERT(cond, s)          \
    do {                         \
        if (cond) {              \
            GREEN;               \
            printf("[  OK  ]    %s\n", s); \
            RESET;               \
        } else {                 \
            RED;                 \
            printf("[ FAIL ]    Failed assertion! '%s'", s); \
            RESET;               \
            printf(" @ %s:%d\n", __FILE__, __LINE__); \
            teardown(1);         \
        }                        \
    } while (0)

/*
 * @brief Rungime assertions for debug mode ONLY.
 * Meant to improve performance of release builds
 *
 * @param cond Condition to assert TRUE
 * @param s    String to log on assertion pass/fail
 */
#define WEAK_ASSERT(cond, s)     
#ifdef MODE_DEBUG
    ASSERT(cond, s)
#endif

/*
 * @brief Prints debug level message to console
 *
 * @param level Level at which to print (INFO, ERRO, WARN)
 * @param s     String to log with leader
 */
#define DBG_MSG(level, s)        \
    do {                         \
        switch(level) {          \
        case INFO:               \
            printf("[ INFO ]    %s\n", s); \
            break;               \
        case ERRO:               \
            RED;                 \
            printf("[ ERRO ]    %s\n", s); \
            RESET;               \
            break;               \
        case WARN:               \
            YELLOW;              \
            printf("[ WARN ]    %s\n", s); \
            RESET;               \
            break;               \
        case VERB:               \
            printf("[ VERB ]    %s\n", s); \
            break;               \
        }                        \
    } while (0)
