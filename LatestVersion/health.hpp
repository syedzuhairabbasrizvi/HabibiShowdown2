#pragma once

#include <iostream>
#include <SDL.h>

using namespace std;

class Health {
protected:
    int value; //current health
    int maxHealth; //maximum health

public: //mostly self explanatory functions
    Health(int h);
    void healthbar(SDL_Renderer* Renderer, int x, int y, int w, int h, SDL_Color FGColor, SDL_Color BGColor, int playerNo);
    void displayHealth() const;
    void operator-=(int damage); //operator overloading successfully implemented!
    bool operator>(int threshold) const;
    int getHealth() const;

};
