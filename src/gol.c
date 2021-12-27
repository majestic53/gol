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

#define BIT_OFFSET(_X_, _Y_) \
    (((_Y_) * WIDTH) / sizeof(uint8_t)) + ((_X_) / sizeof(uint8_t))

#define BYTE_OFFSET(_X_, _Y_) \
    (((_Y_) * (WIDTH / sizeof(uint8_t))) + (_X_))

#define CELL_CHECK(_GOL_, _X_, _Y_) \
    ((_GOL_)->previous[BIT_OFFSET(_X_, _Y_)] & BIT_MASK(_X_))

#define CELL_CLEAR(_GOL_, _X_, _Y_) \
    ((_GOL_)->next[BIT_OFFSET(_X_, _Y_)] &= ~BIT_MASK(_X_))

#define CELL_INIT(_GOL_, _X_, _Y_) \
    ((_GOL_)->previous[BIT_OFFSET(_X_, _Y_)] |= BIT_MASK(_X_))

#define CELL_SET(_GOL_, _X_, _Y_) \
    ((_GOL_)->next[BIT_OFFSET(_X_, _Y_)] |= BIT_MASK(_X_))

typedef struct {
    uint8_t previous[(WIDTH / sizeof(uint8_t)) * (HEIGHT / sizeof(uint8_t))];
    uint8_t next[(WIDTH / sizeof(uint8_t)) * (HEIGHT / sizeof(uint8_t))];
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

static inline void
gol_display(
    __in const gol_t *gol
    )
{

    for(uint32_t y = 0; y < (HEIGHT / sizeof(uint8_t)); ++y) {

        for(uint32_t x = 0; x < (WIDTH / sizeof(uint8_t)); ++x) {
            uint8_t row = gol->previous[BYTE_OFFSET(x, y)];

            for(uint8_t idx = 0; idx < sizeof(uint8_t); ++idx) {
                gol_service_pixel(row & 1, x * sizeof(uint8_t), y * sizeof(uint8_t));
                row >>= 1;
            }
        }
    }
}

static inline void
gol_init(
    __inout gol_t *gol
    )
{
    srand(time(NULL));

    for(uint32_t y = 0; y < HEIGHT; ++y) {

        for(uint32_t x = 0; x < WIDTH; ++x) {

            if(rand() & 1) {
                CELL_INIT(gol, x, y);
            }
        }
    }
}

static inline void
gol_step(
    __inout gol_t *gol
    )
{

    for(uint32_t y = 0; y < HEIGHT; ++y) {

        for(uint32_t x = 0; x < WIDTH; ++x) {
            uint8_t count = 0;

            for(uint8_t index = 0; index < 8; ++index) {
                const gol_coordinate_t *offset = &OFFSET[index];

                if(CELL_CHECK(gol, (x + offset->x) % WIDTH, (y + offset->y) % HEIGHT)) {
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

    memcpy(gol->previous, gol->next, sizeof(gol->next));
}

int
gol(void)
{
    int result;
    gol_t gol = {};

    if((result = gol_service_init()) != EXIT_SUCCESS) {
        goto exit;
    }

    gol_init(&gol);

    while(gol_service_poll()) {
        gol_step(&gol);
        gol_display(&gol);

        if((result = gol_service_show()) != EXIT_SUCCESS) {
            goto exit;
        }
    }

exit:
    gol_service_uninit();

    return result;
}
