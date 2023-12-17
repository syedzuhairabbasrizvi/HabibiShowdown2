#pragma once

#include <SDL.h>
#include <SDL_image.h>
//names are self explanatory, details explained in cpp
SDL_Texture* loadTexture(const char* imagePath, SDL_Renderer* renderer);
bool initSDL(SDL_Window*& window, SDL_Renderer*& renderer, const char* title, int width, int height);
void closeSDL(SDL_Window*& window, SDL_Renderer*& renderer);
