
#include <SDL_image.h>
#include "MatchManager.hpp"
#include "Character.hpp"
#include "SDLHelper.hpp"

using namespace std;

int main(int argc, char* args[]) {
    const char* windowTitle = "Habibi Showdown 2: Electric Boogaloo"; //title
    int windowWidth = 800; //width of window
    int windowHeight = 600; //and height

    SDL_Window* window = nullptr; //to refer to window
    SDL_Renderer* renderer = nullptr; //and renderer

    if (!initSDL(window, renderer, windowTitle, windowWidth, windowHeight)) //error handling
        return -1;

    //loading images using SDL
    SDL_Surface* beginSurface = IMG_Load("E:/HUNotes/Sophomore_Fall/2_OOP/oopProject/HabibiShowdown2-main/start.png");
    SDL_Surface* matchSurface = IMG_Load("E:/HUNotes/Sophomore_Fall/2_OOP/oopProject/HabibiShowdown2-main/bg.jpg");
    SDL_Surface* endSurface = IMG_Load("E:/HUNotes/Sophomore_Fall/2_OOP/oopProject/HabibiShowdown2-main/gameover.png");
    SDL_Surface* playerOneSurface = IMG_Load("E:/HUNotes/Sophomore_Fall/2_OOP/oopProject/HabibiShowdown2-main/pineapple.png");
    SDL_Surface* playerTwoSurface = IMG_Load("E:/HUNotes/Sophomore_Fall/2_OOP/oopProject/HabibiShowdown2-main/watermelon.png");

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

    SDL_Rect orig1Rect = {50, 500, 50, 50};  //beginning positions of my characters
    SDL_Rect orig2Rect = {200, 500, 50, 50};
    
    SDL_Rect player1Rect = orig1Rect;  //starting position of players
    SDL_Rect player2Rect = orig2Rect; 

    Character character1("Kyo", 100, 100);
    Character character2("Iori", 100, 100);
    //initial state and texture

    MatchManager mm{"Begin"}; //begin state constructor
    SDL_Texture* currentTexture = beginTexture; //and beginning texture

    bool quit = false; //to check if we are quitting project
    SDL_Event e; //the entire event is e

    unordered_set<SDL_Keycode> pressedKeys; //this keeps a record of keys pressed in keyboard

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
                character1.move(player1Rect, pressedKeys, 1);
                character2.move(player2Rect, pressedKeys, 2);
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

        if (character1.getJumpState() || character2.getJumpState())
            {
                if (character1.getJumpState())
                    character1.gravity(player1Rect);
                else
                    character2.gravity(player2Rect);
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

    return 0;
}
