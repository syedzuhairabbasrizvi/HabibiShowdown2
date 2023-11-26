#include "gameloop.hpp"

GameLoop::GameLoop() : window(nullptr), renderer(nullptr), character1(nullptr), character2(nullptr), currentTexture(nullptr), mm("Begin") {}

GameLoop::~GameLoop() {
    cleanUp();
}


bool GameLoop::init()
{
    const char* windowTitle = "Habibi Showdown 2: Electric Boogaloo"; //title
    int windowWidth = 800; //width of window
    int windowHeight = 600; //and height


    if (!initSDL(window, renderer, windowTitle, windowWidth, windowHeight)) //error handling
        return false;
    if (!loadTextures()) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load textures.");
        return false;
    }
    

    
    //initial state and texture

    currentTexture = beginTexture; //and beginning texture


    unordered_set<SDL_Keycode> pressedKeys; //this keeps a record of keys pressed in keyboard

    character1 = nullptr;
    character2 = nullptr;

    

    return true;
}

bool GameLoop::loadTextures() 
{
    beginTexture = loadTexture("C:/mingw_dev_lib/project/start.png", renderer);
    matchTexture = loadTexture("C:/mingw_dev_lib/project/bg.jpg", renderer);
    endTexture = loadTexture("C:/mingw_dev_lib/project/gameover.png", renderer);
    playerOneTexture = loadTexture("C:/mingw_dev_lib/project/pineapple.png", renderer);
    playerTwoTexture = loadTexture("C:/mingw_dev_lib/project/watermelon.png", renderer);
    playerOneAttackTexture = loadTexture("C:/mingw_dev_lib/project/angrypineapple.png", renderer);
    playerTwoAttackTexture = loadTexture("C:/mingw_dev_lib/project/angrywatermelon.jpg", renderer);

    // Handle errors or continue with rendering
    if (!beginTexture || !matchTexture || !endTexture || !playerOneTexture || !playerTwoTexture || !playerOneAttackTexture || !playerTwoAttackTexture) {
        // Handle error or return -1
        return false;
    }
    return true;
}

void GameLoop::run() {
    quit = false;

    while (!quit) {
        handleEvents();
        update();
        render();
    }
}

void GameLoop::handleEvents() 
{
    while (SDL_PollEvent(&e) != 0) //not sure what this means, picked it up online
    {
        if (e.type == SDL_QUIT) 
            quit = true; //quit the game once app closed
        else if (e.type == SDL_KEYDOWN) 
        {
            pressedKeys.insert(e.key.keysym.sym); //record the key pressed until it is released
        } 
        else if (e.type == SDL_KEYUP) //key released, free from pressed keys
            pressedKeys.erase(e.key.keysym.sym);
        else if (e.type == SDL_MOUSEBUTTONDOWN) //currently, switch states of game using mouse button. this will be changed later for match to end state
        {
            //switch state and texture on mouse click
            if (mm.getGameState() == "Begin") 
            {
                SDL_Rect orig1Rect = {200, 500, 50, 50};  //beginning positions of my characters
                SDL_Rect orig2Rect = {550, 500, 50, 50};
                character1= new PlayerCharacter("Kyo", 200, 100, 1, orig1Rect);
                character2 = new PlayerCharacter("Iori", 200, 100, 2, orig2Rect);
                mm.setGameState("Match");
                attackOne = false; //checks if we are attacking or not
                attackTwo = false;
                currentTexture = matchTexture;
            } 
            else if (mm.getGameState() == "Match") 
            {
                delete character1;
                delete character2;
                character1 = nullptr;
                character2 = nullptr;
                mm.setGameState("End");
                currentTexture = endTexture;
            } 
            else if (mm.getGameState() == "End") 
            {
                mm.setGameState("Begin");
                currentTexture = beginTexture;
                //reset player positions to their original positions
            }
        }
    }
}


void GameLoop::update()
{
    //player 1 movement using WASD, may replace with a function instead
    if (mm.getGameState() == "Match")
    {
        character1->move(pressedKeys, *character2);
        character2->move(pressedKeys, *character1);

        character1->attackHandler(pressedKeys, *character2);
        character2->attackHandler(pressedKeys, *character1);

        if (character1->getJumpState() || character2->getJumpState())
        {
            if (character1->getJumpState())
                character1->gravity(*character2);
            if (character2->getJumpState())
                character2->gravity(*character1);
        }
    }
}


void GameLoop::render()
{
    //clear the screen
    SDL_RenderClear(renderer);

    //render the current texture
    SDL_RenderCopy(renderer, currentTexture, nullptr, nullptr);

    if (mm.getGameState() == "Match") //only render players once it is match state
    {
        SDL_Rect playerOneRect = character1->getHitbox();
        SDL_Rect playerTwoRect = character2->getHitbox();

        if (character1->getAttackState())
            SDL_RenderCopy(renderer, playerOneAttackTexture, nullptr, &playerOneRect);
        else
            SDL_RenderCopy(renderer, playerOneTexture, nullptr, &playerOneRect);
        if (character2->getAttackState())
            SDL_RenderCopy(renderer, playerTwoAttackTexture, nullptr, &playerTwoRect);
        else
            SDL_RenderCopy(renderer, playerTwoTexture, nullptr, &playerTwoRect);

        character1->renderHealth(renderer);
        character2->renderHealth(renderer);
    }

    //and update the screen
    SDL_RenderPresent(renderer);
}

void GameLoop::cleanUp()
{
    //free resources once game is truly over
    SDL_DestroyTexture(beginTexture);
    SDL_DestroyTexture(matchTexture);
    SDL_DestroyTexture(endTexture);
    SDL_DestroyTexture(playerOneTexture);
    SDL_DestroyTexture(playerTwoTexture);
    SDL_DestroyTexture(playerOneAttackTexture);
    SDL_DestroyTexture(playerTwoAttackTexture);
    //close SDL and free resources
    closeSDL(window, renderer);
}
