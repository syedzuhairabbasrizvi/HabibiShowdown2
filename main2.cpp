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

    // Load images using SDL_image
    SDL_Surface* beginSurface = IM
    
    
    
    
    
    
    
    G_Load("C:/mingw_dev_lib/project/start.png");
    SDL_Surface* matchSurface = IMG_Load("C:/mingw_dev_lib/project/images.jfif");
    SDL_Surface* endSurface = IMG_Load("C:/mingw_dev_lib/project/end.jfif");

    if (beginSurface == nullptr || matchSurface == nullptr || endSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    // Create textures from surfaces
    SDL_Texture* beginTexture = SDL_CreateTextureFromSurface(renderer, beginSurface);
    SDL_Texture* matchTexture = SDL_CreateTextureFromSurface(renderer, matchSurface);
    SDL_Texture* endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);

    SDL_FreeSurface(beginSurface);
    SDL_FreeSurface(matchSurface);
    SDL_FreeSurface(endSurface);

    if (beginTexture == nullptr || matchTexture == nullptr || endTexture == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initial state and texture
    MatchManager mm{"Begin"};
    SDL_Texture* currentTexture = beginTexture;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                // Switch state and texture on mouse click
                if (mm.getGameState() == "Begin") {
                    mm.setGameState("Match");
                    currentTexture = matchTexture;
                } else if (mm.getGameState() == "Match") {
                    mm.setGameState("End");
                    currentTexture = endTexture;
                } else if (mm.getGameState() == "End") {
                    mm.setGameState("Begin");
                    currentTexture = beginTexture;
                }
            }
        }

        // Clear the screen
        SDL_RenderClear(renderer);

        // Render the current texture
        SDL_RenderCopy(renderer, currentTexture, nullptr, nullptr);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Free resources
    SDL_DestroyTexture(beginTexture);
    SDL_DestroyTexture(matchTexture);
    SDL_DestroyTexture(endTexture);

    // Close SDL and free resources
    closeSDL(window, renderer);

    return 0;
}
