#include "health.hpp"
#include <iostream>

Health::Health(int h) : value(h), maxHealth(200) {}


//the framework of the following function was taken from online because we did not know how to display a rectangle, and modified accordingly to suit our project.
void Health::healthbar(SDL_Renderer* Renderer, int x, int y, int w, int h, SDL_Color FGColor, SDL_Color BGColor, int playerNo) {
    float Percent = 1 - float(value)/float(maxHealth); //how much of our health is green?
    SDL_Color old; 
    SDL_GetRenderDrawColor(Renderer, &old.r, &old.g, &old.b, &old.a);
    SDL_Rect bgrect = { x, y, w, h }; //rectangle of the background i.e. red
    SDL_SetRenderDrawColor(Renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a); //render bg color
    SDL_RenderFillRect(Renderer, &bgrect); //and fill it
    SDL_SetRenderDrawColor(Renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a); //render fg color
    int pw = (int)((float)w * Percent); //calculating the length we need to draw by multiplying percentage with width
    int px = x + (2-playerNo)*(w - pw); //this is to determine the x position of the health bar based on the player number
    SDL_Rect fgrect = { px, y, pw, h }; //above process but for green foreground
    SDL_RenderFillRect(Renderer, &fgrect);
    SDL_SetRenderDrawColor(Renderer, old.r, old.g, old.b, old.a);
}

void Health::displayHealth() const {
} //used for error checking earlier

void Health::operator-=(int damage) { //whenever we want to subtract the health, just use this operator overloaded function
        value -= damage;
        if (value < 0) {
            value = 0;
        }
    }

bool Health::operator>(int threshold) const //another operator overloaded function for comparison 
{
        return value > threshold;
}

int Health::getHealth() const { //simple getter
    return value;
}