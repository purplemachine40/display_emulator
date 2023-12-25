#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "screen_data.h"

// Define the display dimensions and pixel size
#define DISPLAY_WIDTH_VIRTUAL_PIXELS 32
#define DISPLAY_HEIGHT_VIRTUAL_PIXELS 32
#define PIXEL_SIZE 10
#define DISPLAY_WIDTH (DISPLAY_WIDTH_VIRTUAL_PIXELS * PIXEL_SIZE)
#define DISPLAY_HEIGHT (DISPLAY_HEIGHT_VIRTUAL_PIXELS * PIXEL_SIZE)
#define WINDOW_WIDTH DISPLAY_WIDTH
#define WINDOW_HEIGHT (2 * DISPLAY_HEIGHT)

#define BUTTON_WIDTH (8 * PIXEL_SIZE)
#define BUTTON_HEIGHT (5 * PIXEL_SIZE)
#define BUTTON_X (12 * PIXEL_SIZE)
#define BUTTON_Y (DISPLAY_HEIGHT + (8 * PIXEL_SIZE))

// Define the colors for black and gray pixels
#define BLACK 0x000000FF
#define GRAY 0x808080FF

// A function that renders the pixels from the screen data array
void render_pixels(SDL_Renderer* renderer)
{
    uint8_t *pScreenData = GetZebraScreenData();
    // Clear the renderer with gray color
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderClear(renderer);

    // Loop through the screen data array
    for (int i = 0; i < DISPLAY_WIDTH_VIRTUAL_PIXELS * DISPLAY_HEIGHT_VIRTUAL_PIXELS / 8; i++)
    {
        // Get the current byte from the array
        unsigned char byte = pScreenData[i];

        // Loop through the bits in the byte
        for (int j = 0; j < 8; j++)
        {
            // Get the bit value (0 or 1)
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

            // Set the pixel color based on the bit value
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

            // Fill the pixel rectangle
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Present the renderer
    // SDL_RenderPresent(renderer);
}

bool isPointInButton(int x, int y)
{
    return (x >= BUTTON_X && x <= BUTTON_X + BUTTON_WIDTH &&
        y >= BUTTON_Y && y <= BUTTON_Y + BUTTON_HEIGHT);
}

int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Grayscale LCD Display Emulator",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // A flag to indicate if the program is running
    int running = 1;

    // A variable to store the events
    SDL_Event e;

    render_pixels(renderer);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = DISPLAY_HEIGHT;
    rect.w = WINDOW_WIDTH;
    rect.h = WINDOW_HEIGHT - DISPLAY_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0xff, 0xaa, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    rect.x = BUTTON_X;
    rect.y = BUTTON_Y;
    rect.w = BUTTON_WIDTH;
    rect.h = BUTTON_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0x99, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);

    // The main loop
    while (running)
    {
        // Handle the events

        while (SDL_PollEvent(&e) != 0)
        {
            // If the user closes the window, quit the program
            switch (e.type)
            {
            case SDL_QUIT:
            {
                running = 0;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (isPointInButton(mouseX, mouseY))
                {
                    printf("Button was Clicked!\n");
                }
            }
            }
        }
    }

    // Destroy the renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}