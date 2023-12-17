#pragma once


#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MatchManager.hpp"
#include "PlayerCharacter.hpp"
#include "SDLHelper.hpp"
#include "health.hpp"
#include "animator.hpp"
#include "time.hpp"
#include <SDL_mixer.h>
#include "Iori.hpp"
#include "Kyo.hpp"

using namespace std;

class GameLoop
{
    public:
        GameLoop();  //default constructor
        ~GameLoop(); //destructor

        bool init(); 
        void run();
    private:
        SDL_Window* window;
        SDL_Renderer* renderer;
        bool quit;
        SDL_Event e;
        Mix_Music* startUpMusic;
        Mix_Music* matchMusic;
        Mix_Music* winMusic;
        bool isMusicPlaying;
        

        bool attackOne, attackTwo, gameEndingTwo = false;

        Animator bgAnimator;
        
        //following are all the miscellanous textures of the game

        SDL_Texture* beginTexture;
        SDL_Texture* endTexture;
        SDL_Texture* bg0;
        SDL_Texture* bg1;
        SDL_Texture* bg2;
        SDL_Texture* bg3;
        SDL_Texture* bg4;
        SDL_Texture* bg5;
        SDL_Texture* bg6;
        SDL_Texture* bg7;
        SDL_Texture* IoriWin;
        SDL_Texture* KyoWin;
        SDL_Texture* health_1;
        SDL_Texture* health_2;
        SDL_Texture* clockbg;

        MatchManager mm; //keeps track of the state of the game

        PlayerCharacter* character1; //these are pointers of base class so that we can perform polymorphism!
        PlayerCharacter* character2;

        Timer* timer;  //add a time instance
        TTF_Font* font; //and the font

        SDL_Texture* currentTexture; 
        std::unordered_set<SDL_Keycode> pressedKeys; //maintains the record of the keys pressed in the game

        //following functions are self explanatory

        bool loadTextures(); 
        void handleEvents();
        void update();
        void render();
        void cleanUp();
};