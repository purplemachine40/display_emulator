#include "Display.h"
#include "UiCommon.h"
#include "ScreenData.h"

uint8_t dispBuf[DISPLAY_BUF_SIZE];

void DrawDisplay(SDL_Renderer* renderer)
{
    // Clear the renderer with gray color
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderClear(renderer);

    // Loop through the screen data array
    for (int i = 0; i < DISPLAY_WIDTH_VIRTUAL_PIXELS * DISPLAY_HEIGHT_VIRTUAL_PIXELS / 8; i++)
    {
        unsigned char byte = dispBuf[i];

        // Loop through the bits in the byte
        for (int j = 0; j < 8; j++)
        {     
            int bit = (byte >> (7 - j)) & 1;

            // Calculate the pixel coordinates
            int x = (i * 8 + j) % DISPLAY_WIDTH_VIRTUAL_PIXELS;
            int y = (i * 8 + j) / DISPLAY_WIDTH_VIRTUAL_PIXELS;

            // Calculate the pixel rectangle
            SDL_Rect rect;
            rect.x = x * PIXEL_SIZE;
            rect.y = y * PIXEL_SIZE;
            rect.w = PIXEL_SIZE;
            rect.h = PIXEL_SIZE;

            if (bit == 1)
            {
                // Black pixel
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            }
            else
            {
                // Gray pixel
                SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
            }

            SDL_RenderFillRect(renderer, &rect);
        }
    }
}


void SetDisplayData(uint8_t* pDispBuf, uint32_t sizeBuf)
{
    if (DISPLAY_BUF_SIZE == sizeBuf)
    {
        SDL_memcpy(&dispBuf[0], pDispBuf, sizeBuf);
    }
}
