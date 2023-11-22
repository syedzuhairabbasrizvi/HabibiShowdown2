#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
void closeSDL(SDL_Window*& window, SDL_Renderer*& renderer);
