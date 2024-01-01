#include "buttons.h"
#include "common_types.h"
#include "display.h"
#include "screen_data.h"
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include "ui_common.h"

static SDL_Window* window;
static SDL_Renderer* pRenderer;

static uint8_t InitializeButtons(SDL_Renderer* pRenderer);

uint8_t InitUi(void)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // Create a window
    window = SDL_CreateWindow(
        "Grayscale LCD Display Emulator",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    // Create a renderer
    pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (pRenderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return FALSE;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("Error initializing SDL_image: %s\n", IMG_GetError());
        return FALSE;
    }

    if (!InitializeButtons(pRenderer))
    {
        printf("Error initializing buttons.\n");
        return FALSE;
    }

    InitDispData();

    return TRUE;
}


void DestroyUi(void)
{
    DesroyButtons();
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


void DrawUI(void)
{
    SetDisplayData(GetCurrentScreenData(), DISPLAY_BUF_SIZE);
    DrawDisplay(pRenderer);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = DISPLAY_HEIGHT;
    rect.w = WINDOW_WIDTH;
    rect.h = WINDOW_HEIGHT - DISPLAY_HEIGHT;
    SDL_SetRenderDrawColor(pRenderer, 0xff, 0xaa, 0x00, 0xFF);
    SDL_RenderFillRect(pRenderer, &rect);

    DrawAllButtons();

    SDL_RenderPresent(pRenderer);
}

SDL_Window* GetWindow(void)
{
    return window;
}

SDL_Renderer* GetRenderer(void)
{
    return pRenderer;
}


static uint8_t InitializeButtons(SDL_Renderer* pRenderer)
{
    TS_BUTTON_SETTUP btnSetup;

    btnSetup.destRect[b_UP].x = UP_BUTTON_X;
    btnSetup.destRect[b_UP].y = UP_BUTTON_Y;
    btnSetup.destRect[b_UP].w = BUTTON_WIDTH;
    btnSetup.destRect[b_UP].h = BUTTON_HEIGHT;

    btnSetup.destRect[b_DOWN].x = DOWN_BUTTON_X;
    btnSetup.destRect[b_DOWN].y = DOWN_BUTTON_Y;
    btnSetup.destRect[b_DOWN].w = BUTTON_WIDTH;
    btnSetup.destRect[b_DOWN].h = BUTTON_HEIGHT;

    btnSetup.destRect[b_LEFT].x = LEFT_BUTTON_X;
    btnSetup.destRect[b_LEFT].y = LEFT_BUTTON_Y;
    btnSetup.destRect[b_LEFT].w = BUTTON_WIDTH;
    btnSetup.destRect[b_LEFT].h = BUTTON_HEIGHT;

    btnSetup.destRect[b_RIGHT].x = RIGHT_BUTTON_X;
    btnSetup.destRect[b_RIGHT].y = RIGHT_BUTTON_Y;
    btnSetup.destRect[b_RIGHT].w = BUTTON_WIDTH;
    btnSetup.destRect[b_RIGHT].h = BUTTON_HEIGHT;

    btnSetup.destRect[b_CENTER].x = SELECT_BUTTON_X;
    btnSetup.destRect[b_CENTER].y = SELECT_BUTTON_Y;
    btnSetup.destRect[b_CENTER].w = BUTTON_WIDTH;
    btnSetup.destRect[b_CENTER].h = BUTTON_HEIGHT;

    btnSetup.pRender = pRenderer;

    return InitButtons(btnSetup);
}
