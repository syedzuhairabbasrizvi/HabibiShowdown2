#include "PlayerCharacter.hpp"
#include <SDL_image.h>
#include "SDLHelper.hpp"
#pragma once


class Iori:public PlayerCharacter
{
    private:
        SDL_Texture* playerOneTextures[5]; //these are all arrays containing textures specific to iori. we iterate through them to create an animation!
        SDL_Texture* playerOneAttackTexture;
        SDL_Texture* playerOneMoveTextures[8];
        SDL_Texture* playerOneBackTextures[9];
        SDL_Texture* playerOnePunchTextures[5];
        SDL_Texture* playerOneHitTextures[4];
        SDL_Texture* playerOneDefeatTextures[11];
        
        vector<int> playerOneMoveWidths; //and these are vectors storing widths and heights of certain animations, otherwise things would look really wonky
        vector<int> playerOneBackWidths;
        vector<int> playerOnePunchWidths;
        vector<int> playerOneHitHeights;
        vector<int> playerOneHitWidths;
        vector<int> playerOnDefeatWidths;
        vector<int> playerOneDefeatWidths;
        vector<int> playerOneDefeatHeights;

        SDL_Texture* playerOneJumpUpTexture;
        SDL_Texture* playerOneJumpDownTexture;
    public:
        Iori(std::string n, int h, int s, int playerNumber, SDL_Rect hb, bool d, SDL_Renderer* renderer);
        void display(SDL_Renderer* renderer,SDL_Rect& playerOneRect, std::unordered_set<SDL_Keycode>& pressedKeys); //this function overrides the display function of playercharacter to achieve polymorphism
        ~Iori();
};