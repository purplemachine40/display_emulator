#include "buttons.h"
#include "common_types.h"
#include <SDL_image.h>
#include "ui_common.h"

#define ACTIVE_X 80
#define UP_Y 0
#define DOWN_Y 60
#define LEFT_Y 120
#define RIGHT_Y 180
#define CENTER_Y 240

typedef struct _TS_BUTTON_DISP_INFO
{
    uint32_t yBtnOffset;
    uint8_t isActive;
}TS_BUTTON_DISP_INFO;

static TS_BUTTON_SETTUP btnSetup;
static SDL_Texture* pTexture;
static  SDL_Rect btnSourceRect;
static TS_BUTTON_DISP_INFO btnDispInfo[b_TOTAL_BUTTONS] =
{
    {UP_Y, FALSE},
    {DOWN_Y, FALSE},
    {LEFT_Y, FALSE},
    {RIGHT_Y, FALSE},
    {CENTER_Y, FALSE},
};

static void DrawButton(TE_BUTTONS btn, uint8_t isClicked);
static void SetBtnX(uint8_t isClicked);
static void RenderButton(uint8_t isClicked, SDL_Rect* pDestRect);
static uint8_t isPointInButton(int x, int y, TE_BUTTONS btn);
static uint8_t ButtonIsValid(TE_BUTTONS btn);

uint8_t InitButtons(TS_BUTTON_SETTUP setup)
{
    btnSetup = setup;
    pTexture = IMG_LoadTexture(btnSetup.pRender, "./img/buttons.png");    
    if (pTexture == NULL)
    {
        return FALSE;
    }
    
    btnSourceRect.x = 0;
    btnSourceRect.y = 0;
    btnSourceRect.w = 80;
    btnSourceRect.h = 60;

    ClearActiveButtons();

    return TRUE;
}


void DesroyButtons(void)
{
    SDL_DestroyTexture(pTexture);
}


void SetButtonActive(TE_BUTTONS btn, uint8_t isActive)
{
    if (ButtonIsValid(btn))
    {
        btnDispInfo[btn].isActive = isActive;
    }
}

uint8_t HasActiveButton(void)
{
    for (int i = 0; i < b_TOTAL_BUTTONS; i++)
    {
        if (btnDispInfo[i].isActive)
        {
            return TRUE;
        }
    }
    return FALSE;
}

void ClearActiveButtons(void)
{
    for (int i = 0; i < b_TOTAL_BUTTONS; i++)
    {
        SetButtonActive(i, FALSE);
    }
}


void DrawAllButtons(void)
{
    for (int i = 0; i < b_TOTAL_BUTTONS; i++)
    {
        DrawButton(i, btnDispInfo[i].isActive);
    }
}


TE_BUTTONS ButtonIsClicked(int mouseX, int mouseY)
{
    for (int i = 0; i < b_TOTAL_BUTTONS; i++)
    {
        if (isPointInButton(mouseX, mouseY, i))
        {
            return i;
        }
    }
    return b_INVALID;
}


static void DrawButton(TE_BUTTONS btn, uint8_t isClicked)
{
    if (ButtonIsValid(btn))
    {
        btnSourceRect.y = btnDispInfo[btn].yBtnOffset;
        RenderButton(isClicked, &btnSetup.destRect[btn]);
    }
}


static void SetBtnX(uint8_t isClicked)
{
    btnSourceRect.x = isClicked ? ACTIVE_X : 0;
}


static void RenderButton(uint8_t isClicked, SDL_Rect* pDestRect)
{
    SetBtnX(isClicked);
    SDL_RenderCopy(btnSetup.pRender, pTexture, &btnSourceRect, pDestRect);
}

static uint8_t isPointInButton(int x, int y, TE_BUTTONS btn)
{
    if (ButtonIsValid(btn))
    {
        return (x >= btnSetup.destRect[btn].x && x <= btnSetup.destRect[btn].x + BUTTON_WIDTH &&
            y >= btnSetup.destRect[btn].y && y <= btnSetup.destRect[btn].y + BUTTON_HEIGHT);
    }
    return FALSE;
}

static uint8_t ButtonIsValid(TE_BUTTONS btn)
{
    return (btn >= 0 && btn < b_TOTAL_BUTTONS);
}