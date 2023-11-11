#include <SDL.h>
#include <SDL_image.h>
#include "MatchManager.hpp"
#include "SDLHelper.hpp"

int main(int argc, char* args[]) {
    const char* windowTitle = "SDL Image Example";
    int windowWidth = 800;
    int windowHeight = 600;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (!initSDL(window, renderer, windowTitle, windowWidth, windowHeight)) {
        return -1;
    }

    // Load image using SDL_image
    SDL_Surface* surface = IMG_Load("C:/mingw_dev_lib/project/7poe0j.png");
    if (surface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the texture
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Free resources
    SDL_DestroyTexture(texture);

    // Close SDL and free resources
    closeSDL(window, renderer);
    MatchManager mm{"Test"};
    mm.printGameState();
    return 0;
}