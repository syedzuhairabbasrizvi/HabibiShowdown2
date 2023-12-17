#include "Iori.hpp"

Iori::Iori(std::string n, int h, int s, int playerNumber, SDL_Rect hb, bool d, SDL_Renderer* renderer) : PlayerCharacter(n,h,s,playerNumber,hb,d) //filling all the variables already described in hpp
{
    playerOneTextures[0] = loadTexture("IoriYagami_0.png", renderer); //very ugly code thanks to needing to separately name the images. we're just loading textures into variables
    playerOneTextures[1] = loadTexture("IoriYagami_2.png", renderer);
    playerOneTextures[2] = loadTexture("IoriYagami_4.png", renderer);
    playerOneTextures[3] = loadTexture("IoriYagami_6.png", renderer);
    playerOneTextures[4] = loadTexture("IoriYagami_8.png", renderer);
    playerOneJumpUpTexture = loadTexture("IoriYagami_30.png", renderer);
    playerOneJumpDownTexture = loadTexture("IoriYagami_31.png", renderer);
    
    playerOneMoveTextures[0] = loadTexture("IoriYagami_54.png", renderer);
    playerOneMoveTextures[1] = loadTexture("IoriYagami_55.png", renderer);
    playerOneMoveTextures[2] = loadTexture("IoriYagami_56.png", renderer);
    playerOneMoveTextures[3] = loadTexture("IoriYagami_57.png", renderer);
    playerOneMoveTextures[4] = loadTexture("IoriYagami_58.png", renderer);
    playerOneMoveTextures[5] = loadTexture("IoriYagami_59.png", renderer);
    playerOneMoveTextures[6] = loadTexture("IoriYagami_60.png", renderer);
    playerOneMoveTextures[7] = loadTexture("IoriYagami_61.png", renderer);

    playerOneBackTextures[0] = loadTexture("IoriYagami_19.png", renderer);
    playerOneBackTextures[1] = loadTexture("IoriYagami_20.png", renderer);
    playerOneBackTextures[2] = loadTexture("IoriYagami_21.png", renderer);
    playerOneBackTextures[3] = loadTexture("IoriYagami_22.png", renderer);
    playerOneBackTextures[4] = loadTexture("IoriYagami_23.png", renderer);
    playerOneBackTextures[5] = loadTexture("IoriYagami_24.png", renderer);
    playerOneBackTextures[6] = loadTexture("IoriYagami_25.png", renderer);
    playerOneBackTextures[7] = loadTexture("IoriYagami_26.png", renderer);
    playerOneBackTextures[8] = loadTexture("IoriYagami_27.png", renderer);

    playerOnePunchTextures[0] = loadTexture("IoriYagami_211.png", renderer);
    playerOnePunchTextures[1] = loadTexture("IoriYagami_212.png", renderer);
    playerOnePunchTextures[2] = loadTexture("IoriYagami_213.png", renderer);
    playerOnePunchTextures[3] = loadTexture("IoriYagami_214.png", renderer);
    playerOnePunchTextures[4] = loadTexture("IoriYagami_215.png", renderer);

    playerOneHitTextures[0] = loadTexture("IoriYagami_567.png", renderer);
    playerOneHitTextures[1] = loadTexture("IoriYagami_568.png", renderer);
    playerOneHitTextures[2] = loadTexture("IoriYagami_569.png", renderer);
    playerOneHitTextures[3] = loadTexture("IoriYagami_570.png", renderer);
    
    playerOneDefeatTextures[0] = loadTexture("IoriYagami_610.png", renderer);
    playerOneDefeatTextures[1] = loadTexture("IoriYagami_611.png", renderer);
    playerOneDefeatTextures[2] = loadTexture("IoriYagami_612.png", renderer);
    playerOneDefeatTextures[3] = loadTexture("IoriYagami_613.png", renderer);
    playerOneDefeatTextures[4] = loadTexture("IoriYagami_614.png", renderer);
    playerOneDefeatTextures[5] = loadTexture("IoriYagami_615.png", renderer);
    playerOneDefeatTextures[6] = loadTexture("IoriYagami_616.png", renderer);
    playerOneDefeatTextures[7] = loadTexture("IoriYagami_617.png", renderer);
    playerOneDefeatTextures[8] = loadTexture("IoriYagami_589.png", renderer);
    playerOneDefeatTextures[9] = loadTexture("IoriYagami_590.png", renderer);

    hitSound = Mix_LoadWAV("V_Iori_Damage_01.wav"); //note that two of these are sounds (chunks) and one is a music. this is because the first two superimpose on top of the pre playing music, while the last one plays on its own. so we used different types accordingly.
    punchSound = Mix_LoadWAV("V_Iori_Atk_01.wav");
    deathSound = Mix_LoadMUS("V_Iori_Dead_01.wav");

    setGameRun(); //only doing for Iori since we need just one character to set the game as running
    for (int i = 0; i < 5; i++) //now storing textures into respective frames
        storeNeutralFrame(playerOneTextures[i]);

    for (int i = 0; i < 4; i++)
        storeHitFrame(playerOneHitTextures[i]);

    for (int i = 0; i < 8; i++)
        storeMoveFrame(playerOneMoveTextures[i]);

    for (int i = 0; i < 9; i++)
        storeBackFrame(playerOneBackTextures[i]);

    for (int i = 0; i < 5; i++)
        storePunchFrame(playerOnePunchTextures[i]);

    for (int i = 0; i < 10; i++)
        storeDefeatFrame(playerOneDefeatTextures[i]);

    playerOneMoveWidths = {80, 96, 80, 16, 80, 80, 80, 16}; //initializing all the widths and heights. actually, the names are misleading since these are the amounts by which widths/heights increase, not the actual widths and heights themselves.

    playerOneBackWidths = {-32, -32, -64, -64, -48, -48, -64, -64, -32};
    playerOnePunchWidths = {16, 80, 64, 32, 0};


    playerOneHitWidths = {0, 0, 32, 0};
    playerOneHitHeights= {16, 16, 48, 16};
    playerOneDefeatWidths = {0, 0, 0, 0, 0, 0, 0, 96, 128, 128};
    playerOneDefeatHeights = {16, 16, 16, 16, -80, -80, -80, -112, -80, -112};
    //160, 208 -> 80 104 wrote this for calculation
                
}

void Iori::display(SDL_Renderer* renderer,SDL_Rect& playerOneRect, std::unordered_set<SDL_Keycode>& pressedKeys)
{
    if (getDefeatState()) //if iori is defeated, play the animation 
    {
        playerOneRect.w += playerOneDefeatWidths[defeatAnimator.getCurrent()]; //fix widths, heights, x and y
        playerOneRect.x -= playerOneDefeatWidths[defeatAnimator.getCurrent()];
        playerOneRect.h += playerOneDefeatHeights[defeatAnimator.getCurrent()];
        if (playerOneDefeatHeights[defeatAnimator.getCurrent()] < -100) //the images where iori is on the ground are slightly above ground, so we push the y position lower to compnsate
            playerOneRect.y += 20;
        playerOneRect.y -= playerOneDefeatHeights[defeatAnimator.getCurrent()];
        
        currentTexture = defeatAnimator.animate(200); //animate with cooldown 200 (the greater this value, the slower the animation)
    }
    else if (getHitState()) //handle hit state similarly
    {
        playerOneRect.w += playerOneHitWidths[hitAnimator.getCurrent()];
        playerOneRect.y -= playerOneHitHeights[hitAnimator.getCurrent()];
        playerOneRect.h += playerOneHitHeights[hitAnimator.getCurrent()];
        currentTexture = hitAnimator.animate(100); //faster jonny
    }
    else if (this->getJumpState()) //the this pointer wasnt really needed, but we developed this code earlier before realizing a better way as above
        {
            if (this->getUpState()) //i dont think i really need to explain these blocks of code now
                
                {
                playerOneRect.w -= 64;
                currentTexture = playerOneJumpUpTexture;
                }
            else 
                {
                playerOneRect.w -= 32;
                currentTexture = playerOneJumpDownTexture;
                }
        }
        else if (this->getAttackState())
        {
            playerOneRect.w += playerOnePunchWidths[this->punchAnimator.getCurrent()];
            currentTexture = this->punchAnimator.animate(100);
        }
        else if (this->getMovingState(pressedKeys))
        {
            if (this->facingForwards())
            {
                playerOneRect.w += playerOneMoveWidths[this->moveAnimator.getCurrent()];
                playerOneRect.h -= 32;
                playerOneRect.y += 32;
                currentTexture = this->moveAnimator.animate(200);
            }
            
            else
            {
                playerOneRect.w += playerOneBackWidths[this->backAnimator.getCurrent()];
                currentTexture = this->backAnimator.animate(200);
            }
        }
        else
            currentTexture = this->neutralAnimator.animate(200);
        this->PlayerCharacter::display(renderer, playerOneRect, pressedKeys); //finally call the base class's function that is declared virtual
}

Iori::~Iori()
{
    for (int i = 0; i < 5; i++) //destroy All the textures.
        SDL_DestroyTexture(playerOneTextures[i]);
    SDL_DestroyTexture(playerOneJumpDownTexture);
    SDL_DestroyTexture(playerOneJumpUpTexture);
    for (int i = 0; i < 8; i++)
        SDL_DestroyTexture(playerOneMoveTextures[i]);
    for (int i = 0; i < 9; i++)
        SDL_DestroyTexture(playerOneBackTextures[i]);
    for (int i = 0; i < 5; i++)
        SDL_DestroyTexture(playerOnePunchTextures[i]);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture(playerOneHitTextures[i]);
    for (int i = 0; i < 10; i++)
        SDL_DestroyTexture(playerOneDefeatTextures[i]);
}
