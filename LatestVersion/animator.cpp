#include "animator.hpp"

void Animator::pushFrame(SDL_Texture* frame){
    frames.push_back(frame);
}

SDL_Texture* Animator::animate(int limit){
    if (current == 0)
        on = true;
    cooldown += 1;
    if (cooldown >= limit)
    {
        cooldown = 0;
        current += 1;
        current %= frames.size();
        if (current == 0)
            on = false;
    }
    return frames[current];
}

int Animator::getCurrent()
{
    return current;
}

bool Animator::isOn()
{
    return on;
}