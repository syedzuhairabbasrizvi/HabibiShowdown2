#include "gameloop.hpp"

#include <SDL_image.h>

using namespace std;

int main(int argc, char* args[]) 
{
    GameLoop gameLoop;
    if (!gameLoop.init()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize the game loop.");
        return -1;
    }

    gameLoop.run();

    return 0;
    
}
