#pragma once

#include <SDL.h>

uint8_t InitUi(void);
void DestroyUi(void);
void DrawUI(void);
SDL_Window* GetWindow(void);
SDL_Renderer* GetRenderer(void);
