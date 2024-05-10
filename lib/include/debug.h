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
#include <stdlib.h>
#include <unistd.h>

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
            char buf[100];       \
            sprintf(buf, "Failed assertion! '%s'", s); \
                                 \
            DBG_MSG(ERRO, buf);  \
            teardown(1);          \
        }                        \
    } while (0)

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
