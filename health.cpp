#include "health.hpp"
#include <iostream>

Health::Health(int h) : value(h), maxHealth(200) {}

void Health::healthbar(SDL_Renderer* Renderer, int x, int y, int w, int h, SDL_Color FGColor, SDL_Color BGColor) {
    float Percent = 1 - float(value)/float(maxHealth);
    SDL_Color old;
    SDL_GetRenderDrawColor(Renderer, &old.r, &old.g, &old.b, &old.a);
    SDL_Rect bgrect = { x, y, w, h };
    SDL_SetRenderDrawColor(Renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(Renderer, &bgrect);
    SDL_SetRenderDrawColor(Renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int)((float)w * Percent);
    int px = x + (w - pw);
    SDL_Rect fgrect = { px, y, pw, h };
    SDL_RenderFillRect(Renderer, &fgrect);
    SDL_SetRenderDrawColor(Renderer, old.r, old.g, old.b, old.a);
}

void Health::displayHealth() const {
}

void Health::takeDamage(int damage) {
    value -= damage;
    if (value < 0) {
        value = 0;
        std::cout << "Try Again! You lost.";
    }
    if (value < 10) {
    }
    // If other player's value = 0; you won
}

