#pragma once

typedef enum _TE_SYSTEM_EVENT
{
    se_NONE,
    se_UP_BTN_PRESSED,
    se_DOWN_BTN_PRESSED,
    se_LEFT_BTN_PRESSED,
    se_RIGHT_BTN_PRESSED,
    se_CENTER_BTN_PRESSED,
    se_POWER_BTN_PRESSED,
    se_BACK_BTN_PRESSED,    
    se_BUTTON_RELEASED,
    se_REFRESH_DISPLAY,
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

void InitEventGenerator(void);
void UpdateEvents(void);
TE_SYSTEM_EVENT GetSysEvent(void);
void ClearSysEvent(void);
TE_EMULATOR_EVENT GetEmulatorEvent(void);
