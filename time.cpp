// Timer.cpp
#include "time.hpp"

Timer::Timer(SDL_Renderer* renderer, int screenWidth, int fontSize)
    : renderer(renderer), startTime(0), timerTexture(nullptr), font(nullptr), screenWidth(screenWidth) {
    // Initialize font
    font = TTF_OpenFont("C:/Users/Aqeel/Downloads/Open_Sans/OpenSans-VariableFont_wdth,wght.ttf", fontSize);
    if (!font) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

void Timer::start() {
    startTime = SDL_GetTicks();
}

/*
void Timer::update() {
    // Update logic if needed
}
*/

void Timer::render() {
    if (font) {
        // Calculate the remaining time
        int elapsedTime = (SDL_GetTicks() - startTime) / 1000;
        int remainingTime = std::max(60 - elapsedTime, 0);

        // Convert remaining time to string
        std::string timeText = "Timer: " + std::to_string(remainingTime);

        // Load and render the font texture
        loadFontTexture(timeText);

        int textWidth, textHeight;
        SDL_QueryTexture(timerTexture, nullptr, nullptr, &textWidth, &textHeight);

        SDL_Rect timerRect = {(screenWidth - textWidth) / 2, 10, textWidth, textHeight};
        SDL_RenderCopy(renderer, timerTexture, nullptr, &timerRect);
    }
}

void Timer::loadFontTexture(const std::string& text) {
    if (timerTexture != nullptr) {
        SDL_DestroyTexture(timerTexture);
        timerTexture = nullptr;
    }

    SDL_Color textColor = {0, 0, 0};
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (textSurface == nullptr) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to render text surface! SDL_Error: %s\n", TTF_GetError());
    } else {
        timerTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (timerTexture == nullptr) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from rendered text! SDL_Error: %s\n", SDL_GetError());
        }
        SDL_FreeSurface(textSurface);
    }
}

Timer::~Timer() {
    // Cleanup font
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }

    // Cleanup texture
    if (timerTexture) {
        SDL_DestroyTexture(timerTexture);
        timerTexture = nullptr;
    }
}
