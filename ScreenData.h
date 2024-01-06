#pragma once
#include <SDL.h>

typedef enum _TE_DISPLAY_SCREENS
{
    ds_WELCOME,
    ds_MAIN,
    ds_MAIN_MENU,
    ds_SUB_MENU,
    ds_BLANK,
    ds_TOTAL_SCREENS
}TE_DISPLAY_SCREENS;

void SetScreenData(TE_DISPLAY_SCREENS screen);
uint8_t* GetCurrentScreenData(void);
