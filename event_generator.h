#pragma once

typedef enum _TE_SYSTEM_EVENT
{
    se_NONE,
    se_UP_BTN_PRESSED,
    se_DOWN_BTN_PRESSED,
    se_LEFT_BTN_PRESSED,
    se_RIGHT_BTN_PRESSED,
    se_CENTER_BTN_PRESSED,
    se_BUTTON_RELEASED,
    se_TOTAL_EVENTS,
    se_INVALID_EVENT
}TE_SYSTEM_EVENT;

typedef enum _TE_EMULATOR_EVENT
{
    ee_NONE,
    ee_QUIT,    
    ee_TOTAL_EVENTS,
    ee_INVALID_EVENT
}TE_EMULATOR_EVENT;

void UpdateEvents(void);
TE_SYSTEM_EVENT GetSysEvent(void);
TE_EMULATOR_EVENT GetEmulatorEvent(void);
