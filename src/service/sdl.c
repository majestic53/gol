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

#include <SDL2/SDL.h>
#include "../../include/service.h"

typedef struct {
    uint32_t tick;
    uint32_t pixel[WIDTH][HEIGHT];
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Window *window;
} gol_sdl_t;

static gol_sdl_t g_service = {};

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

static inline int
gol_service_present(void)
{
    int result = EXIT_SUCCESS;

    if(SDL_UpdateTexture(g_service.texture, NULL, g_service.pixel, WIDTH * sizeof(uint32_t))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(SDL_RenderClear(g_service.renderer)) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(SDL_RenderCopy(g_service.renderer, g_service.texture, NULL, NULL)) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    SDL_RenderPresent(g_service.renderer);

exit:
    return result;
}

int
gol_service_clear(void)
{

    for(int y = 0; y < WIDTH; ++y) {

        for(int x = 0; x < HEIGHT; ++x) {
            gol_service_pixel(false, x, y);
        }
    }

    return gol_service_present();
}

int
gol_service_init(void)
{
    int result = EXIT_SUCCESS;

    if(SDL_Init(SDL_INIT_VIDEO)) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(!(g_service.window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH * SCALE, HEIGHT * SCALE, SDL_WINDOW_RESIZABLE))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(!(g_service.renderer = SDL_CreateRenderer(g_service.window, -1, SDL_RENDERER_ACCELERATED))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(SDL_RenderSetLogicalSize(g_service.renderer, WIDTH, HEIGHT)) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(SDL_SetRenderDrawColor(g_service.renderer, 0, 0, 0, 0)) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0") == SDL_FALSE) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    if(!(g_service.texture = SDL_CreateTexture(g_service.renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT))) {
        result = GOL_ERROR(EXIT_FAILURE);
        goto exit;
    }

    gol_service_show();

exit:
    return result;
}

void
gol_service_pixel(
    __in bool alive,
    __in uint32_t x,
    __in uint32_t y
    )
{
    g_service.pixel[y][x] = alive ? ALIVE : DEAD;
}

bool
gol_service_poll(void)
{
    SDL_Event event;
    bool result = true;

    while(SDL_PollEvent(&event)) {

        switch(event.type) {
            case SDL_QUIT:
                result = false;
                break;
            default:
                break;
        }
    }

    return result;
}

int
gol_service_show(void)
{
    int result;
    uint32_t elapsed;

    if((result = gol_service_present()) != EXIT_SUCCESS) {
        goto exit;
    }

    if((elapsed = (SDL_GetTicks() - g_service.tick)) < (1000 / (float)FPS)) {
        SDL_Delay((1000 / (float)FPS) - elapsed);
    }

    g_service.tick = SDL_GetTicks();

exit:
    return result;
}

void
gol_service_uninit(void)
{

    if(g_service.texture) {
        SDL_DestroyTexture(g_service.texture);
    }

    if(g_service.renderer) {
        SDL_DestroyRenderer(g_service.renderer);
    }

    if(g_service.window) {
        SDL_DestroyWindow(g_service.window);
    }

    SDL_Quit();
    memset(&g_service, 0, sizeof(g_service));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
