#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>

// Define the display dimensions and pixel size
#define DISPLAY_WIDTH 32
#define DISPLAY_HEIGHT 32
#define PIXEL_SIZE 10

// Define the colors for black and gray pixels
#define BLACK 0x000000FF
#define GRAY 0x808080FF

// Define the C array that contains the screen data
// Each bit represents one pixel, 1 for black and 0 for gray
// The array size should be equal to DISPLAY_WIDTH * DISPLAY_HEIGHT / 8
uint8_t screen_data[] = {
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b11111111, 0b11111111, 0b11111111, 0b11111111,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
    0b00000000, 0b00000000, 0b00000000, 0b00000000,
};

// A function that renders the pixels from the screen data array
void render_pixels(SDL_Renderer* renderer) {
    // Clear the renderer with gray color
    SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderClear(renderer);

    // Loop through the screen data array
    for (int i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT / 8; i++) {
        // Get the current byte from the array
        unsigned char byte = screen_data[i];

        // Loop through the bits in the byte
        for (int j = 0; j < 8; j++) {
            // Get the bit value (0 or 1)
            int bit = (byte >> (7 - j)) & 1;

            // Calculate the pixel coordinates
            int x = (i * 8 + j) % DISPLAY_WIDTH;
            int y = (i * 8 + j) / DISPLAY_WIDTH;

            // Calculate the pixel rectangle
            SDL_Rect rect;
            rect.x = x * PIXEL_SIZE;
            rect.y = y * PIXEL_SIZE;
            rect.w = PIXEL_SIZE;
            rect.h = PIXEL_SIZE;

            // Set the pixel color based on the bit value
            if (bit == 1) {
                // Black pixel
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
            }
            else {
                // Gray pixel
                SDL_SetRenderDrawColor(renderer, 0x80, 0x80, 0x80, 0xFF);
            }

            // Fill the pixel rectangle
            SDL_RenderFillRect(renderer, &rect);
        }
    }

    // Present the renderer
    SDL_RenderPresent(renderer);
}

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow(
        "Grayscale LCD Display Emulator",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        DISPLAY_WIDTH * PIXEL_SIZE,
        DISPLAY_HEIGHT * PIXEL_SIZE,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // A flag to indicate if the program is running
    int running = 1;

    // A variable to store the events
    SDL_Event e;

    // The main loop
    while (running) {
        // Handle the events
        while (SDL_PollEvent(&e) != 0) {
            // If the user closes the window, quit the program
            if (e.type == SDL_QUIT) {
                running = 0;
            }
        }

        // Render the pixels
        render_pixels(renderer);
    }

    // Destroy the renderer and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}