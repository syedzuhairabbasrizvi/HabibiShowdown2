#pragma once

#include <vector>
#include <SDL_image.h>

using namespace std;

class Animator
{
    private:
        vector<SDL_Texture*> frames;
        int current = 0;
        int cooldown;
        bool on = false;
    public:
        void pushFrame(SDL_Texture* image);
        SDL_Texture* animate(int limit);
        int getCurrent();
        bool isOn();
};