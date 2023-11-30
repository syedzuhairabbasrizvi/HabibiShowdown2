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
    beginTexture = loadTexture("C:/weekly4/start.png", renderer);
    endTexture = loadTexture("C:/weekly4/gameover.png", renderer);
    playerOneTextureA = loadTexture("C:/weekly4/IoriYagami_0.png", renderer);
    playerOneTextureB = loadTexture("C:/weekly4/IoriYagami_2.png", renderer);
    playerOneTextureC = loadTexture("C:/weekly4/IoriYagami_4.png", renderer);
    playerOneTextureD = loadTexture("C:/weekly4/IoriYagami_6.png", renderer);
    playerOneTextureE = loadTexture("C:/weekly4/IoriYagami_8.png", renderer);
    playerTwoTextureA = loadTexture("C:/weekly4/ExKyo_0.png", renderer);
    playerTwoTextureB = loadTexture("C:/weekly4/ExKyo_2.png", renderer);
    playerTwoTextureC = loadTexture("C:/weekly4/ExKyo_4.png", renderer);
    playerTwoTextureD = loadTexture("C:/weekly4/ExKyo_6.png", renderer);
    playerTwoTextureE = loadTexture("C:/weekly4/ExKyo_8.png", renderer);
    playerOneAttackTexture = loadTexture("C:/weekly4/IoriYagami_164.png", renderer);
    playerTwoAttackTexture = loadTexture("C:/weekly4/ExKyo_119.png", renderer);
    playerOneMoveTexture = loadTexture("C:/weekly4/IoriYagami_55.png", renderer);
    playerTwoMoveTexture = loadTexture("C:/weekly4/ExKyo_55.png", renderer);
    bg0 = loadTexture("C:/weekly4/park/frame_0.png", renderer);
    bg1 = loadTexture("C:/weekly4/park/frame_1.png", renderer);
    bg2 = loadTexture("C:/weekly4/park/frame_2.png", renderer);
    bg3 = loadTexture("C:/weekly4/park/frame_3.png", renderer);
    bg4 = loadTexture("C:/weekly4/park/frame_4.png", renderer);
    bg5 = loadTexture("C:/weekly4/park/frame_5.png", renderer);
    bg6 = loadTexture("C:/weekly4/park/frame_6.png", renderer);
    bg7 = loadTexture("C:/weekly4/park/frame_7.png", renderer);
    bgAnimator.pushFrame(bg0);
    bgAnimator.pushFrame(bg1);
    bgAnimator.pushFrame(bg2);
    bgAnimator.pushFrame(bg3);
    bgAnimator.pushFrame(bg4);
    bgAnimator.pushFrame(bg5);
    bgAnimator.pushFrame(bg6);
    bgAnimator.pushFrame(bg7);
    // Handle errors or continue with rendering
    if (!beginTexture || !bg0 || !endTexture || !playerOneTextureA || !playerTwoTextureA || !playerOneAttackTexture || !playerTwoAttackTexture) {
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
                SDL_Rect orig1Rect = {200, 350, 144, 224};  //beginning positions of my characters; z - kyo size is 112^2
                SDL_Rect orig2Rect = {550, 350, 144, 224};
                character1= new PlayerCharacter("Iori", 200, 100, 1, orig1Rect);
                character2 = new PlayerCharacter("Kyo", 200, 100, 2, orig2Rect);
                character1->storeNeutralFrame(playerOneTextureA);
                character1->storeNeutralFrame(playerOneTextureB);
                character1->storeNeutralFrame(playerOneTextureC);
                character1->storeNeutralFrame(playerOneTextureD);
                character1->storeNeutralFrame(playerOneTextureE);
                character2->storeNeutralFrame(playerTwoTextureA);
                character2->storeNeutralFrame(playerTwoTextureB);
                character2->storeNeutralFrame(playerTwoTextureC);
                character2->storeNeutralFrame(playerTwoTextureD);
                character2->storeNeutralFrame(playerTwoTextureE);

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
        currentTexture = bgAnimator.animate(150);
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

    SDL_RenderCopy(renderer, currentTexture, nullptr, nullptr);
    //render the current texture

    if (mm.getGameState() == "Match") //only render players once it is match state
    {
        SDL_Rect playerOneRect = character1->getHitbox();
        SDL_Rect playerTwoRect = character2->getHitbox();
        if (character1->getAttackState())
        {
            playerOneRect.w += 48;
            SDL_RenderCopyEx(renderer, playerOneAttackTexture, NULL, &playerOneRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else if (character1->getMovingState(pressedKeys))
        {
            playerOneRect.w += 112;
            playerOneRect.h -= 32;
            playerOneRect.y += 32;
            SDL_RenderCopyEx(renderer, playerOneMoveTexture, NULL, &playerOneRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        }
        else
            SDL_RenderCopyEx(renderer, character1->neutralAnimator.animate(200), NULL, &playerOneRect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
        if (character2->getAttackState())
        {
            playerTwoRect.w += 96;
            playerTwoRect.x -= 50;
            SDL_RenderCopy(renderer, playerTwoAttackTexture, nullptr, &playerTwoRect);
        }
        else if (character2->getMovingState(pressedKeys))
        {
            playerTwoRect.w += 106;
            SDL_RenderCopy(renderer, playerTwoMoveTexture, nullptr, &playerTwoRect);
        }
        else
            SDL_RenderCopy(renderer, character2->neutralAnimator.animate(200), nullptr, &playerTwoRect);

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
    SDL_DestroyTexture(playerOneTextureA);
    SDL_DestroyTexture(playerOneTextureB);
    SDL_DestroyTexture(playerOneTextureC);
    SDL_DestroyTexture(playerOneTextureD);
    SDL_DestroyTexture(playerOneTextureE);
    SDL_DestroyTexture(playerTwoTextureA);
    SDL_DestroyTexture(playerTwoTextureB);
    SDL_DestroyTexture(playerTwoTextureC);
    SDL_DestroyTexture(playerTwoTextureD);
    SDL_DestroyTexture(playerTwoTextureE);
    SDL_DestroyTexture(bg0);
    SDL_DestroyTexture(bg1);
    SDL_DestroyTexture(bg2);
    SDL_DestroyTexture(bg3);
    SDL_DestroyTexture(bg4);
    SDL_DestroyTexture(bg5);
    SDL_DestroyTexture(bg6);
    SDL_DestroyTexture(bg7);
    SDL_DestroyTexture(playerOneAttackTexture);
    SDL_DestroyTexture(playerTwoAttackTexture);
    SDL_DestroyTexture(playerOneMoveTexture);
    //close SDL and free resources
    closeSDL(window, renderer);
}
