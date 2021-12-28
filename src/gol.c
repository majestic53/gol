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

#include <time.h>
#include "../include/gol.h"
#include "../include/service.h"

#define BIT_MASK(_X_) \
    (1 << ((_X_) % sizeof(uint8_t)))

#define BIT_OFFSET(_GOL_, _X_, _Y_) \
    (((_Y_) * (_GOL_)->width) / sizeof(uint8_t)) + ((_X_) / sizeof(uint8_t))

#define BYTE_OFFSET(_GOL_, _X_, _Y_) \
    (((_Y_) * ((_GOL_)->width / sizeof(uint8_t))) + (_X_))

#define CELL_CHECK(_GOL_, _X_, _Y_) \
    ((_GOL_)->previous[BIT_OFFSET(_GOL_, _X_, _Y_)] & BIT_MASK(_X_))

#define CELL_CLEAR(_GOL_, _X_, _Y_) \
    ((_GOL_)->next[BIT_OFFSET(_GOL_, _X_, _Y_)] &= ~BIT_MASK(_X_))

#define CELL_INIT(_GOL_, _X_, _Y_) \
    ((_GOL_)->previous[BIT_OFFSET(_GOL_, _X_, _Y_)] |= BIT_MASK(_X_))

#define CELL_SET(_GOL_, _X_, _Y_) \
    ((_GOL_)->next[BIT_OFFSET(_GOL_, _X_, _Y_)] |= BIT_MASK(_X_))

typedef struct {
    size_t width;
    size_t height;
    uint8_t *previous;
    uint8_t *next;
} gol_t;

typedef struct {
    int32_t x;
    int32_t y;
} gol_coordinate_t;

static const gol_coordinate_t OFFSET[] = {
    { -1, -1 },
    {  0, -1 },
    {  1, -1 },
    { -1,  0 },
    {  1,  0 },
    { -1,  1 },
    {  0,  1 },
    {  1,  1 },
    };

static void
gol_display(
    __in const gol_t *gol
    )
{

    for(uint32_t y = 0; y < (gol->height / sizeof(uint8_t)); ++y) {

        for(uint32_t x = 0; x < (gol->width / sizeof(uint8_t)); ++x) {
            uint8_t row = gol->previous[BYTE_OFFSET(gol, x, y)];

            for(uint8_t idx = 0; idx < sizeof(uint8_t); ++idx) {
                gol_service_pixel(row & 1, x * sizeof(uint8_t), y * sizeof(uint8_t));
                row >>= 1;
            }
        }
    }
}

static int
gol_init(
    __inout gol_t *gol,
    __in unsigned width,
    __in uint32_t height
    )
{
    int result = EXIT_SUCCESS;

    srand(time(NULL));
    gol->width = width;
    gol->height = height;

    if(!(gol->previous = calloc((gol->width / sizeof(uint8_t)) * (gol->height / sizeof(uint8_t)), sizeof(uint8_t)))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(!(gol->next = calloc((gol->width / sizeof(uint8_t)) * (gol->height / sizeof(uint8_t)), sizeof(uint8_t)))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    for(uint32_t y = 0; y < gol->height; ++y) {

        for(uint32_t x = 0; x < gol->width; ++x) {

            if(rand() & 1) {
                CELL_INIT(gol, x, y);
            }
        }
    }

exit:
    return result;
}

static void
gol_step(
    __inout gol_t *gol
    )
{

    for(uint32_t y = 0; y < gol->height; ++y) {

        for(uint32_t x = 0; x < gol->width; ++x) {
            uint8_t count = 0;

            for(uint8_t index = 0; index < 8; ++index) {
                const gol_coordinate_t *offset = &OFFSET[index];

                if(CELL_CHECK(gol, (x + offset->x) % gol->width, (y + offset->y) % gol->height)) {
                    ++count;
                }
            }

            if(CELL_CHECK(gol, x, y)) {

                if((count < 2) || (count > 3)) {
                    CELL_CLEAR(gol, x, y);
                } else {
                    CELL_SET(gol, x, y);
                }
            } else {

                if(count == 3) {
                    CELL_SET(gol, x, y);
                } else {
                    CELL_CLEAR(gol, x, y);
                }
            }
        }
    }

    memcpy(gol->previous, gol->next, (gol->width / sizeof(uint8_t)) * (gol->height / sizeof(uint8_t)));
}

static void
gol_uninit(
    __inout gol_t *gol
    )
{

    if(gol->next) {
        free(gol->next);
    }

    if(gol->previous) {
        free(gol->previous);
    }

    memset(gol, 0, sizeof(*gol));
}

int
gol(
    __in unsigned long width,
    __in unsigned long height
    )
{
    int result;
    gol_t gol = {};

    if((result = gol_service_init(width, height)) != EXIT_SUCCESS) {
        goto exit;
    }

    if((result = gol_init(&gol, width, height)) != EXIT_SUCCESS) {
        goto exit;
    }

    while(gol_service_poll()) {
        gol_step(&gol);
        gol_display(&gol);

        if((result = gol_service_show()) != EXIT_SUCCESS) {
            goto exit;
        }
    }

exit:
    gol_uninit(&gol);
    gol_service_uninit();

    return result;
}
