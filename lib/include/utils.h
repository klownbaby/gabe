/* 
 * Copyright (C) 2024 Kevin Kleiman - All Rights Reserved
 * You may use, distribute and modify this code under the
 * for any purpose
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: , or visit :
 */

#pragma once

/* Define goto macros for success/fail conditions */
#define GOTO_SUCCESS goto success
#define GOTO_FAIL    goto fail

#define GOTO_SUCCESS_IF(cond) \
    do { if (cond) goto success; } while(0)
#define GOTO_FAIL_IF(cond)    \
    do { if (cond) goto fail; } while(0)

