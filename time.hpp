// Timer.hpp
#pragma once

#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

class Timer {
public:
    Timer(SDL_Renderer* renderer, int screenWidth, int fontSize);   //construct timer using sdl, screen width, font size.
    ~Timer();       //bye bye timer no one will miss you

    void start();   //start the timer
    void update();  //idk i prolly will delete this one, ignore for now
    void render();  //render the tiemr

private:
    Uint32 startTime;   //the actual ticking
    SDL_Texture* timerTexture;  //shaheer says i shouldnt worry about this one
    SDL_Renderer* renderer;     //important thing i guess?
    TTF_Font* font;             //the font to use
    int screenWidth;
    
    void loadFontTexture(const std::string& text);  //oh god
};

