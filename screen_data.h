#pragma once
#include <SDL.h>

typedef enum _TE_DISPLAY_SCREENS
{
    ds_WELCOME,
    ds_MAIN_SCREEN,
    ds_MENU_SCREEN,
    ds_TOTAL_SCREENS
}TE_DISPLAY_SCREENS;

void SetScreenData(TE_DISPLAY_SCREENS screen);
uint8_t* GetCurrentScreenData(void);
uint8_t* GetZebraScreenData(void);
uint8_t* GetMainScreenData(void);