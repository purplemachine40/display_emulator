#include "event_generator.h"
#include <stdlib.h>
#include "screen_data.h"
#include "ui.h"


int main(int argc, char* argv[])
{
    int running = 1;

    if(!InitUi())
    {        
        return 1;
    }

    DrawUI();
    
    while (running)
    {
        UpdateEvents();
        if (GetSysEvent() != se_NONE)
        {
            SetScreenData(ds_MAIN_SCREEN);
            DrawUI();            
        }

        if (GetEmulatorEvent() == ee_QUIT)
        {
            running = 0;
        }
    }

    DestroyUi();
    return 0;
}