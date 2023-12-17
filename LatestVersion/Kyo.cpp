#include "Kyo.hpp"
//read iori.cpp to understand
Kyo::Kyo(std::string n, int h, int s, int playerNumber, SDL_Rect hb, bool d, SDL_Renderer* renderer) : PlayerCharacter(n,h,s,playerNumber,hb,d)
{
    playerTwoTextures[0] = loadTexture("ExKyo_0.png", renderer);
    playerTwoTextures[1] = loadTexture("ExKyo_2.png", renderer);
    playerTwoTextures[2] = loadTexture("ExKyo_4.png", renderer);
    playerTwoTextures[3] = loadTexture("ExKyo_6.png", renderer);
    playerTwoTextures[4] = loadTexture("ExKyo_8.png", renderer);

    playerTwoJumpUpTexture = loadTexture("ExKyo_23.png", renderer);
    playerTwoJumpDownTexture = loadTexture("ExKyo_24.png", renderer);
    
    playerTwoPunchTextures[0] = loadTexture("ExKyo_112.png", renderer);
    playerTwoPunchTextures[1] = loadTexture("ExKyo_113.png", renderer);
    playerTwoPunchTextures[2] = loadTexture("ExKyo_114.png", renderer);
    playerTwoPunchTextures[3] = loadTexture("ExKyo_115.png", renderer);
    playerTwoPunchTextures[4] = loadTexture("ExKyo_116.png", renderer);

    playerTwoMoveTextures[0] = loadTexture("ExKyo_53.png", renderer);
    playerTwoMoveTextures[1] = loadTexture("ExKyo_54.png", renderer);
    playerTwoMoveTextures[2] = loadTexture("ExKyo_55.png", renderer);
    playerTwoMoveTextures[3] = loadTexture("ExKyo_56.png", renderer);
    playerTwoMoveTextures[4] = loadTexture("ExKyo_57.png", renderer);
    playerTwoMoveTextures[5] = loadTexture("ExKyo_58.png", renderer);

    playerTwoBackTextures[0] = loadTexture("ExKyo_16.png", renderer);
    playerTwoBackTextures[1] = loadTexture("ExKyo_17.png", renderer);
    playerTwoBackTextures[2] = loadTexture("ExKyo_18.png", renderer);
    playerTwoBackTextures[3] = loadTexture("ExKyo_19.png", renderer);
    playerTwoBackTextures[4] = loadTexture("ExKyo_20.png", renderer);


    playerTwoHitTextures[0] = loadTexture("ExKyo_679.png", renderer);
    playerTwoHitTextures[1] = loadTexture("ExKyo_680.png", renderer);
    playerTwoHitTextures[2] = loadTexture("ExKyo_681.png", renderer);
    playerTwoHitTextures[3] = loadTexture("ExKyo_682.png", renderer);

    playerTwoDefeatTextures[0] = loadTexture("ExKyo_712.png", renderer);
    playerTwoDefeatTextures[1] = loadTexture("ExKyo_713.png", renderer);
    playerTwoDefeatTextures[2] = loadTexture("ExKyo_714.png", renderer);
    playerTwoDefeatTextures[3] = loadTexture("ExKyo_715.png", renderer);
    playerTwoDefeatTextures[4] = loadTexture("ExKyo_716.png", renderer);
    playerTwoDefeatTextures[5] = loadTexture("ExKyo_717.png", renderer);
    playerTwoDefeatTextures[6] = loadTexture("ExKyo_718.png", renderer);
    playerTwoDefeatTextures[7] = loadTexture("ExKyo_719.png", renderer);
    playerTwoDefeatTextures[8] = loadTexture("ExKyo_720.png", renderer);
    playerTwoDefeatTextures[9] = loadTexture("ExKyo_700.png", renderer);
    playerTwoDefeatTextures[10] = loadTexture("ExKyo_701.png", renderer);

    playerTwoMoveWidths = {-32, 64, 64, -32, 64, 64};
    playerTwoBackWidths = {0, -64, -64, -64, -32};
    playerTwoHitWidths = {0, 0, 32, 0};
    playerTwoDefeatWidths = {0, 0, 0, 0, -32, -32, -32, 32, 64, 128, 128};
    playerTwoDefeatHeights = {0, 0, -32, -32, -64, -64, -32, -32, -64, -128, -128};
    playerTwoPunchHeights = {-32, -32, 32, 0, 0};
    playerTwoPunchWidths = {-32, 0, 0, -32, -32};
    //160, 224 -> 80, 112

    for (int i = 0; i < 5; i++)
        storeNeutralFrame(playerTwoTextures[i]);
    for (int i = 0; i < 5; i++)
        storePunchFrame(playerTwoPunchTextures[i]);
    for (int i = 0; i < 6; i++)
        storeMoveFrame(playerTwoMoveTextures[i]);
    for (int i = 0; i < 5; i++)
        storeBackFrame(playerTwoBackTextures[i]);
    for (int i = 0; i < 4; i++)
        storeHitFrame(playerTwoHitTextures[i]);
    for (int i = 0; i < 11; i++)
        storeDefeatFrame(playerTwoDefeatTextures[i]);

    hitSound = Mix_LoadWAV("V_Kyo_Damage_01.wav");
    punchSound = Mix_LoadWAV("V_Kyo_Atk_01.wav");
    deathSound = Mix_LoadMUS("V_Kyo_Dead_01.wav");
}

void Kyo::display(SDL_Renderer* renderer,SDL_Rect& playerTwoRect, std::unordered_set<SDL_Keycode>& pressedKeys)
{
    if (getDefeatState())
    {
        playerTwoRect.w += playerTwoDefeatWidths[defeatAnimator.getCurrent()];
        playerTwoRect.x -= playerTwoDefeatWidths[defeatAnimator.getCurrent()];
        playerTwoRect.h += playerTwoDefeatHeights[defeatAnimator.getCurrent()];
        if (playerTwoDefeatHeights[defeatAnimator.getCurrent()] < -100)
            playerTwoRect.y += 20;
        playerTwoRect.y -= playerTwoDefeatHeights[defeatAnimator.getCurrent()];
        currentTexture = defeatAnimator.animate(200);
    }
    else if (getJumpState())
    {
        if (getUpState())
        {
            playerTwoRect.w -= 32;
            currentTexture = playerTwoJumpUpTexture;
        }
        else 
            currentTexture = playerTwoJumpDownTexture;
    }
    else if (getHitState())
    {
        playerTwoRect.w += playerTwoHitWidths[hitAnimator.getCurrent()];
        currentTexture = hitAnimator.animate(100);
    }
    else if (getAttackState())
    {
        playerTwoRect.w += playerTwoPunchWidths[this->punchAnimator.getCurrent()];
        playerTwoRect.y -= playerTwoPunchHeights[this->punchAnimator.getCurrent()];
        playerTwoRect.h += playerTwoPunchHeights[this->punchAnimator.getCurrent()];
        currentTexture = punchAnimator.animate(100);                                                                                        
    }
    else if (getMovingState(pressedKeys))
    {
        if (facingForwards())
        {
            playerTwoRect.w += playerTwoMoveWidths[moveAnimator.getCurrent()];
            currentTexture = moveAnimator.animate(200);
        }
        else
        {
            playerTwoRect.w += playerTwoBackWidths[backAnimator.getCurrent()];
            currentTexture = backAnimator.animate(200);
        }
    }
    else
        currentTexture = neutralAnimator.animate(200);
    PlayerCharacter::display(renderer, playerTwoRect, pressedKeys);
}

Kyo::~Kyo()
{
    SDL_DestroyTexture(playerTwoJumpDownTexture);
    SDL_DestroyTexture(playerTwoJumpUpTexture);
    SDL_DestroyTexture(playerTwoAttackTexture);
    for (int i = 0; i < 5; i++)
        SDL_DestroyTexture(playerTwoTextures[i]);
    for (int i = 0; i < 6; i++)
        SDL_DestroyTexture(playerTwoMoveTextures[i]);
    for (int i = 0; i < 5; i++)
        SDL_DestroyTexture(playerTwoBackTextures[i]);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture(playerTwoHitTextures[i]);
    for (int i = 0; i < 11; i++)
        SDL_DestroyTexture(playerTwoDefeatTextures[i]);
}