#pragma once

#include "Character.hpp"
#include <unordered_set>
#include "health.hpp"

#include <SDL.h>

#include <iostream>
#include <string>

using namespace std;

class PlayerCharacter : public Character
{
    private:
    int playerNum;
    SDL_Keycode rightKey, leftKey, upKey, attackKey;
    Health playerHealth;

    public:

    PlayerCharacter(std::string, int, int, int, SDL_Rect);
    void renderHealth(SDL_Renderer* renderer);
    void gravity(PlayerCharacter& opponent);
    void move(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent);
    void attackHandler(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent);
    void takeDamage(int damage);
};
