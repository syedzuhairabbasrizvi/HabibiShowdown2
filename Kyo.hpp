#include "PlayerCharacter.hpp"
#include <SDL_image.h>
#include "SDLHelper.hpp"
#include <SDL_mixer.h>

#pragma once


class Kyo:public PlayerCharacter //read iori.hpp for explanation, it is structured similarly. Only difference is in textures and handling according to kyo
{
    private:
        SDL_Texture* playerTwoTextures[5];
        SDL_Texture* playerTwoMoveTextures[6];
        SDL_Texture* playerTwoBackTextures[5];
        SDL_Texture* playerTwoHitTextures[4];
        SDL_Texture* playerTwoDefeatTextures[11];
        SDL_Texture* playerTwoPunchTextures[5];

       
        
        vector<int> playerTwoMoveWidths;
        vector<int> playerTwoBackWidths;
        vector<int> playerTwoHitWidths;
        vector<int> playerTwoDefeatWidths;
        vector<int> playerTwoDefeatHeights;
        vector<int> playerTwoPunchWidths;
        vector<int> playerTwoPunchHeights;

        SDL_Texture* playerTwoJumpUpTexture;
        SDL_Texture* playerTwoJumpDownTexture;
        SDL_Texture* playerTwoAttackTexture;

    public:
        Kyo(std::string n, int h, int s, int playerNumber, SDL_Rect hb, bool d, SDL_Renderer* renderer);
        void display(SDL_Renderer* renderer,SDL_Rect& playerTwoRect, std::unordered_set<SDL_Keycode>& pressedKeys);
        ~Kyo();
};