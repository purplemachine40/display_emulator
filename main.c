#include "c_state_machine/c_state_machine.h"
#include "EventGenerator.h"
#include <stdlib.h>
#include "ScreenData.h"
#include "ui.h"


int main(int argc, char* argv[])
{
    int running = 1;

    if(!InitUi())
    {        
        return 1;
    }

    InitAppCode();
    DrawUI();
    
    while (running)
    {
        UpdateEvents();

        if (GetSysEvent() != se_NONE)
        {
            DrawUI();
        }

        AppCode();
        ClearSysEvent();

        if (GetEmulatorEvent() == ee_QUIT)
        {
            running = 0;
        }
    }

    DestroyUi();
    return 0;
}