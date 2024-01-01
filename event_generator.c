#include "buttons.h"
#include "common_types.h"
#include "event_generator.h"
#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _TS_BTN_EVENT_CROSS
{
    TE_BUTTONS btn;
    TE_SYSTEM_EVENT sysEvent;
}TS_BTN_EVENT_CROSS;

static TE_SYSTEM_EVENT sysEvent;
static TE_EMULATOR_EVENT emulatorEvent;
static TS_BTN_EVENT_CROSS btnEventCross[] =
{
    {b_UP, se_UP_BTN_PRESSED},
    {b_DOWN, se_DOWN_BTN_PRESSED},
    {b_LEFT, se_LEFT_BTN_PRESSED},
    {b_RIGHT, se_RIGHT_BTN_PRESSED},
    {b_CENTER, se_CENTER_BTN_PRESSED},
};

static void AddBtnEvent(TE_BUTTONS btn);


void UpdateEvents(void)
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_QUIT:
        {
            emulatorEvent = ee_QUIT;
        }
        break;
        case SDL_MOUSEBUTTONDOWN:
        {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            TE_BUTTONS btn = ButtonIsClicked(mouseX, mouseY);
            if (btn != b_INVALID)
            {
                AddBtnEvent(btn);
                SetButtonActive(btn, TRUE);
            }
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            if (HasActiveButton())
            {
                ClearActiveButtons();
                sysEvent = se_BUTTON_RELEASED;
            }
        }
        break;
        }
    }
}

TE_SYSTEM_EVENT GetSysEvent(void)
{
    TE_SYSTEM_EVENT evt = sysEvent;
    sysEvent = se_NONE;
    return evt;
}

TE_EMULATOR_EVENT GetEmulatorEvent(void)
{
    TE_EMULATOR_EVENT evt = emulatorEvent;
    emulatorEvent = ee_NONE;
    return evt;
}


static void AddBtnEvent(TE_BUTTONS btn)
{
#define SIZE_BTN_CROSS (sizeof(btnEventCross) / sizeof(TS_BTN_EVENT_CROSS))
    for (int i = 0; i < SIZE_BTN_CROSS; i++)
    {
        if (btn == btnEventCross[i].btn)
        {
            sysEvent = btnEventCross[i].sysEvent;
            return;
        }
    }
}