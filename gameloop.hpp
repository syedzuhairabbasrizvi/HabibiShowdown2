#pragma once


#include <SDL_image.h>
#include "MatchManager.hpp"
#include "PlayerCharacter.hpp"
#include "SDLHelper.hpp"
#include "health.hpp"
#include "animator.hpp"

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

        Animator bgAnimator;
        SDL_Texture* beginTexture;
        SDL_Texture* matchTexture;
        SDL_Texture* endTexture;
        SDL_Texture* playerOneTextureA;
        SDL_Texture* playerOneTextureB;
        SDL_Texture* playerOneTextureC;
        SDL_Texture* playerOneTextureD;
        SDL_Texture* playerOneTextureE;
        SDL_Texture* playerTwoTextureA;
        SDL_Texture* playerTwoTextureB;
        SDL_Texture* playerTwoTextureC;
        SDL_Texture* playerTwoTextureD;
        SDL_Texture* playerTwoTextureE;
        SDL_Texture* playerTwoTexture;
        SDL_Texture* playerOneAttackTexture;
        SDL_Texture* playerTwoAttackTexture;
        SDL_Texture* playerOneMoveTexture;
        SDL_Texture* playerTwoMoveTexture;
        SDL_Texture* bg0;
        SDL_Texture* bg1;
        SDL_Texture* bg2;
        SDL_Texture* bg3;
        SDL_Texture* bg4;
        SDL_Texture* bg5;
        SDL_Texture* bg6;
        SDL_Texture* bg7;
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
