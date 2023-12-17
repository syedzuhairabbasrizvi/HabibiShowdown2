#pragma once

#include "Character.hpp"
#include <unordered_set>
#include "health.hpp"
#include <SDL_mixer.h>
#include <SDL.h>

#include <iostream>
#include <string>

using namespace std;

class PlayerCharacter : public Character
{
    protected:
    static bool gameOver;
    int playerNum;
    SDL_Keycode rightKey, leftKey, upKey, attackKey;
    float speed;
    Health playerHealth;
    bool direction;  //left == true and vv
    bool forwards;
    Mix_Chunk* punchSound;
    Mix_Chunk* hitSound;
    Mix_Music* deathSound;
    int channel1;
    int channel2;
    

    public:

    SDL_Texture* currentTexture;  //to keep track of our texture
    PlayerCharacter(std::string, int, int, int, SDL_Rect, bool); 
    void renderHealth(SDL_Renderer* renderer); //to render the health ofc
    void gravity(PlayerCharacter& opponent); //so that we dont fly away after jumping
    void handleDirection(PlayerCharacter& opponent); //fix direction as req
    void move(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent);
    void attackHandler(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent); //honestly the remaining functions are fairly self explanatory so we're not commenting them here in hpp
    void takeDamage(int damage);
    bool getMovingState(unordered_set<SDL_Keycode>& pressedKeys);
    bool facingForwards();
    virtual void display(SDL_Renderer* renderer, SDL_Rect& rect, std::unordered_set<SDL_Keycode>& pressedKeys);
    int getHealth() const;
    bool isGameOver() const;
    void setGameRun();
};
