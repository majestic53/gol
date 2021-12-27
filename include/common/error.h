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

#ifndef GOL_ERROR_H_
#define GOL_ERROR_H_

#include "./define.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GOL_ERROR(_ERR_) \
    gol_error_set(_ERR_, __FILE__, __FUNCTION__, __LINE__)

const char *gol_error(void);

int gol_error_set(
    __in int error,
    __in const char *file,
    __in const char *function,
    __in size_t line
    );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* GOL_ERROR_H_ */
