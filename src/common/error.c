/**
 * Game of Life (GOL)
 * Copyright (C) 2021 David Jolly
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "../../include/common/error.h"

typedef struct {
    int error;
    char str[64];
} gol_error_t;

static gol_error_t g_error = {};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

const char *
gol_error(void)
{
    return g_error.str;
}

int
gol_error_set(
    __in int error,
    __in const char *file,
    __in const char *function,
    __in size_t line
    )
{

    if((g_error.error = error)) {
        snprintf(g_error.str, 64, "%u (%s:%s@%zu)", g_error.error, file, function, line);
    } else {
        memset(&g_error, 0, sizeof(g_error));
    }

    return g_error.error;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
