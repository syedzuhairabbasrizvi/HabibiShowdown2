// Timer.cpp
#include "time.hpp"

Timer::Timer(SDL_Renderer* renderer, int screenWidth, int fontSize)
    : renderer(renderer), startTime(0), timerTexture(nullptr), font(nullptr), screenWidth(screenWidth) {
    //initialize font
    if (TTF_Init() < 0) {
    //handle SDL_ttf initialization error
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "you're an idiot", "\n");
    }
    font = TTF_OpenFont("C:/Windows/Fonts/impact.ttf", fontSize); //handling opening the font
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void Timer::start() {
    startTime = SDL_GetTicks(); //begin the countdown!
}

void Timer::render() {
    if (font) {
        //calculate the remaining time
        int elapsedTime = (SDL_GetTicks() - startTime) / 1000;
        int remainingTime = std::max(99 - elapsedTime, 0);

        //convert remaining time to string
        std::string timeText = std::to_string(remainingTime);

        //load and render the font texture
        loadFontTexture(timeText);

        int textWidth, textHeight;
        SDL_QueryTexture(timerTexture, nullptr, nullptr, &textWidth, &textHeight);

        SDL_Rect timerRect = {(screenWidth - textWidth) / 2+1, 37, textWidth, textHeight};
        SDL_RenderCopy(renderer, timerTexture, nullptr, &timerRect);
    }
}

void Timer::loadFontTexture(const std::string& text) {
    if (timerTexture != nullptr) {
        SDL_DestroyTexture(timerTexture); //so that we can load a new texture, we get rid of the old one
        timerTexture = nullptr;
    }

    SDL_Color textColor = {182, 187, 196}; //color of my color
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor); //rendering the text surface
    if (textSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to render text surface! SDL_Error: %s\n", TTF_GetError());
    } else {
        timerTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (timerTexture == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(textSurface); //free surface after loading
    }
}

Timer::~Timer() {
    //cleanup font
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    //cleanup texture
    if (timerTexture) {
        SDL_DestroyTexture(timerTexture);
        timerTexture = nullptr;
    }
}

