#pragma once

#include <SDL.h>

typedef enum _TE_BUTTONS
{
    b_UP,
    b_DOWN,
    b_LEFT,
    b_RIGHT,
    b_CENTER,    
    b_TOTAL_BUTTONS,
    b_INVALID
}TE_BUTTONS;

typedef struct _TS_BUTTON_SETTUP
{
    SDL_Renderer *pRender;
    SDL_Rect destRect[b_TOTAL_BUTTONS];
}TS_BUTTON_SETTUP;

uint8_t InitButtons(TS_BUTTON_SETTUP setup);
void DesroyButtons(void);
void SetButtonActive(TE_BUTTONS btn, uint8_t isActive);
uint8_t HasActiveButton(void);
void ClearActiveButtons(void);
void DrawAllButtons(void);
TE_BUTTONS ButtonIsClicked(int mouseX, int mouseY);
