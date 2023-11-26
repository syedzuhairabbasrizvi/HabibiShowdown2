#pragma once


#include <SDL_image.h>
#include "MatchManager.hpp"
#include "PlayerCharacter.hpp"
#include "SDLHelper.hpp"
#include "health.hpp"
using namespace std;

class GameLoop
{
    public:
        GameLoop();  // Default constructor
        ~GameLoop(); // Destructor

        bool init();
        void run();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;

        bool quit;
        SDL_Event e;

        bool attackOne, attackTwo;

        SDL_Texture* beginTexture;
        SDL_Texture* matchTexture;
        SDL_Texture* endTexture;
        SDL_Texture* playerOneTexture;
        SDL_Texture* playerTwoTexture;
        SDL_Texture* playerOneAttackTexture;
        SDL_Texture* playerTwoAttackTexture;

        MatchManager mm;

        PlayerCharacter* character1;
        PlayerCharacter* character2;

        SDL_Texture* currentTexture;
        std::unordered_set<SDL_Keycode> pressedKeys;

        bool loadTextures();
        void handleEvents();
        void update();
        void render();
        void cleanUp();
};