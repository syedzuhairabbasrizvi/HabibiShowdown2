#include <SDL.h>
#include <SDL_image.h>
#include "MatchManager.hpp"
#include "SDLHelper.hpp"
#include <unordered_set>

using namespace std;

int main(int argc, char* args[]) {
    const char* windowTitle = "Habibi Showdown 2: Electric Boogaloo"; //title
    int windowWidth = 800; //width of window
    int windowHeight = 600; //and height

    SDL_Window* window = nullptr; //to refer to window
    SDL_Renderer* renderer = nullptr; //and renderer

    if (!initSDL(window, renderer, windowTitle, windowWidth, windowHeight)) //error handling
        return -1;


    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    // Load font
    TTF_Font* font = TTF_OpenFont("path/to/your/font.ttf", 24);  // Replace with your font file path
    if (!font) {
        SDL_Log("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }
    SDL_Color textColor = {255, 255, 255, 255}; // White color



    //loading images using SDL
    SDL_Surface* beginSurface = IMG_Load("C:/mingw_dev_lib/project/maxresdefault.jpg");
    SDL_Surface* matchSurface = IMG_Load("C:/mingw_dev_lib/project/bg.gif");
    SDL_Surface* endSurface = IMG_Load("C:/mingw_dev_lib/project/youdied.jpg");
    SDL_Surface* playerOneSurface = IMG_Load("C:/mingw_dev_lib/project/egg.png");
    SDL_Surface* playerTwoSurface = IMG_Load("C:/mingw_dev_lib/project/egg.png");

    if (beginSurface == nullptr || matchSurface == nullptr || endSurface == nullptr || playerOneSurface == nullptr || playerTwoSurface == nullptr) //error handling if an image doesnt load properly 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    //creating textures from surfaces
    SDL_Texture* beginTexture = SDL_CreateTextureFromSurface(renderer, beginSurface);
    SDL_Texture* matchTexture = SDL_CreateTextureFromSurface(renderer, matchSurface);
    SDL_Texture* endTexture = SDL_CreateTextureFromSurface(renderer, endSurface);
    SDL_Texture* playerOneTexture = SDL_CreateTextureFromSurface(renderer, playerOneSurface);
    SDL_Texture* playerTwoTexture = SDL_CreateTextureFromSurface(renderer, playerTwoSurface);

    //and freeing the surfaces from memory
    SDL_FreeSurface(beginSurface);
    SDL_FreeSurface(matchSurface);
    SDL_FreeSurface(endSurface);
    SDL_FreeSurface(playerOneSurface);
    SDL_FreeSurface(playerTwoSurface);

    if (beginTexture == nullptr || matchTexture == nullptr || endTexture == nullptr || playerOneTexture == nullptr || playerTwoTexture == nullptr) //error handling for texture creation 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    SDL_Rect orig1Rect = {50, 50, 50, 50};  //beginning positions of my characters
    SDL_Rect orig2Rect = {200, 200, 50, 50};
    
    SDL_Rect player1Rect = orig1Rect;  //starting position of players
    SDL_Rect player2Rect = orig2Rect; 

    

    //initial state and texture

    MatchManager mm{"Begin"}; //begin state constructor
    SDL_Texture* currentTexture = beginTexture; //and beginning texture

    bool quit = false; //to check if we are quitting project
    SDL_Event e; //the entire event is e

    unordered_set<SDL_Keycode> pressedKeys; //this keeps a record of keys pressed in keyboard


    Time gameTimer;  // Create an instance of the Timer class
    gameTimer.startTimer();  // Start the timer

    // Player health (example values)
    int playerOneHealth = 100;
    int playerTwoHealth = 100;

    while (!quit) //as long as app is running
    { 
        while (SDL_PollEvent(&e) != 0) //not sure what this means, picked it up online
        {
            if (e.type == SDL_QUIT) 
                quit = true; //quit the game once app closed
            else if (e.type == SDL_KEYDOWN) 
            {
                pressedKeys.insert(e.key.keysym.sym); //record the key pressed until it is released

                //player 1 movement using WASD, may replace with a function instead
                if (pressedKeys.count(SDLK_w)) 
                    player1Rect.y -= 10;
                if (pressedKeys.count(SDLK_a))
                    player1Rect.x -= 10;
                if (pressedKeys.count(SDLK_s))
                    player1Rect.y += 10;
                if (pressedKeys.count(SDLK_d))
                    player1Rect.x += 10;
                //player 2 movement using udlr, see above
                if (pressedKeys.count(SDLK_UP))
                    player2Rect.y -= 10;
                if (pressedKeys.count(SDLK_LEFT))
                    player2Rect.x -= 10;
                if (pressedKeys.count(SDLK_DOWN))
                    player2Rect.y += 10;
                if (pressedKeys.count(SDLK_RIGHT))
                    player2Rect.x += 10;
            } 
            else if (e.type == SDL_KEYUP) //key released, free from pressed keys
                pressedKeys.erase(e.key.keysym.sym);
            else if (e.type == SDL_MOUSEBUTTONDOWN) //currently, switch states of game using mouse button. this will be changed later for match to end state
            {
                //switch state and texture on mouse click
                if (mm.getGameState() == "Begin") 
                {
                    mm.setGameState("Match");
                    currentTexture = matchTexture;
                } 
                else if (mm.getGameState() == "Match") 
                {
                    mm.setGameState("End");
                    currentTexture = endTexture;
                } 
                else if (mm.getGameState() == "End") 
                {
                    mm.setGameState("Begin");
                    currentTexture = beginTexture;
                    //reset player positions to their original positions
                    player1Rect = orig1Rect;
                    player2Rect = orig2Rect;
                }
            }
        }

        // Update the timer
        gameTimer.updateTimer();

        // Render  timer in match state
        if (mm.getGameState() == "Match") {
            std::string timeString = gameTimer.getTimeAsString();
            SDL_Surface* textSurface = TTF_RenderText_Solid(font, timeString.c_str(), textColor);
            SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
            int textWidth = textSurface->w;
            int textHeight = textSurface->h;
            SDL_Rect renderQuad = {10, 10, textWidth, textHeight};
            SDL_RenderCopy(renderer, textTexture, nullptr, &renderQuad);
            SDL_FreeSurface(textSurface);
            SDL_DestroyTexture(textTexture);
        }

        // check player health
        if (playerOneHealth <= 0 || playerTwoHealth <= 0) {
            mm.setGameState("End");
            currentTexture = endTexture;
            gameTimer.stopTimer();
            std::string winner = playerOneHealth <= 0 ? "Player Two Wins" : "Player One Wins";
            SDL_Log("Game Over: %s", winner.c_str());
        }


        //clear the screen
        SDL_RenderClear(renderer);

        //render the current texture
        SDL_RenderCopy(renderer, currentTexture, nullptr, nullptr);

        if (mm.getGameState() == "Match") //only render players once it is match state
        {
            SDL_RenderCopy(renderer, playerOneTexture, nullptr, &player1Rect);
            SDL_RenderCopy(renderer, playerTwoTexture, nullptr, &player2Rect);
        }

        //and update the screen
        SDL_RenderPresent(renderer);
    }

    //free resources once game is truly over
    SDL_DestroyTexture(beginTexture);
    SDL_DestroyTexture(matchTexture);
    SDL_DestroyTexture(endTexture);
    SDL_DestroyTexture(playerOneTexture);
    SDL_DestroyTexture(playerTwoTexture);
    //close SDL and free resources
    closeSDL(window, renderer);

    TTF_CloseFont(font);
    TTF_Quit();
    return 0;
}