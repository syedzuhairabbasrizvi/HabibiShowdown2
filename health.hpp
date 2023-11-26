#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

class Health {
private:
    int value;
    int maxHealth;

public:
    Health(int h);
    void healthbar(SDL_Renderer* Renderer, int x, int y, int w, int h, SDL_Color FGColor, SDL_Color BGColor);
    void displayHealth() const;
    void takeDamage(int damage);
    int getValue()
    {
        return value;
    }
};
