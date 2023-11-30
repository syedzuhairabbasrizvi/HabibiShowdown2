
#include "PlayerCharacter.hpp"

#include <iostream>
PlayerCharacter::PlayerCharacter(std::string n, int h, int s, int playerNumber, SDL_Rect hb) : Character(n, h, s, hb) , playerHealth(h) {

    playerNum=playerNumber;

    if (playerNumber == 2) {
        rightKey = SDLK_RIGHT;
        leftKey = SDLK_LEFT;
        upKey = SDLK_UP;
        attackKey = SDLK_KP_1;
    } else if (playerNumber == 1) {
        rightKey = SDLK_d;
        leftKey = SDLK_a;
        upKey = SDLK_w;
        attackKey = SDLK_j;
    } 


}

void PlayerCharacter::renderHealth(SDL_Renderer* renderer)
{
    playerHealth.healthbar(renderer, 100 + (400*(playerNum-1)), 100, 200, 20, {255, 0, 0, 255}, {0, 255, 0, 255});
}

void PlayerCharacter::gravity(PlayerCharacter& opponent) {
    int static cooldown1 = 0;
    int static cooldown2 = 0;
    int cooldown;
    if (opponent.playerNum == 2)
        cooldown = cooldown1;
    else
        cooldown = cooldown2;
    if (isJumping){
        Uint32 currentTime = SDL_GetTicks();
        Uint32 jumpDuration = currentTime - jumpStartTime;
        cooldown += 1;

        // Adjust the jump duration and gravity speed based on your preferences
        if (jumpDuration < 350 ) 
        {  // Adjust the jump duration (milliseconds)
            if (cooldown >= 3)
            {
                cooldown = 0;
                hitbox.y -= 2;
            }
        } 
        else 
        {
            SDL_Rect opponentHitbox = opponent.getHitbox();
            SDL_Rect newHitbox = hitbox;
            
            if (cooldown >= 3)
            {
                newHitbox.y += 2;
            }
            if ((SDL_HasIntersection(&newHitbox, &opponentHitbox)))
                hitbox.x += 25;
            // Apply gravity after the jump duration
            if (cooldown >= 3)
            {
                cooldown = 0;
                hitbox.y += 2;  // Adjust the gravity speed
            }
        }

        // Check if the player has reached  ground
        if (hitbox.y >= 350) { // Adjust the ground level as needed
            hitbox.y = 350; // Set the player back to the ground
            isJumping = false; // Reset the jumping state
        }
    }
    if (opponent.playerNum == 2)
        cooldown1 = cooldown;
    else
        cooldown2 = cooldown;
}

void PlayerCharacter::move(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent) {
    // Adjust keys based on player number
    int static cooldown1 = 0;
    int static cooldown2 = 0;
    int cooldown;
    if (opponent.playerNum == 2)
        cooldown = cooldown1;
    else
        cooldown = cooldown2;
    if (!(isHit || isAttack))
    {
        // Inside the move function of PlayerCharacter
        SDL_Rect opponentHitbox = opponent.getHitbox();
        // Jump action
        if (pressedKeys.count(upKey) && !isJumping) {
            // If the Up key is pressed and the player is not already jumping
            isJumping = true;
            jumpStartTime = SDL_GetTicks();  // Record the start time of the jump

        }

        // Simulate character movement based on keyboard input
        if (pressedKeys.count(rightKey) && hitbox.x != 750) {
            SDL_Rect newHitbox = hitbox;
            newHitbox.x += 1;
            if (!(SDL_HasIntersection(&newHitbox, &opponentHitbox)))
            {
                cooldown += 1;
                if (cooldown >= 2)
                {
                    hitbox.x += 1;
                    cooldown = 0;
                }
            }
        }

        if (pressedKeys.count(leftKey)  && hitbox.x != 0 ) 
        {
            SDL_Rect newHitbox = hitbox;
            newHitbox.x -= 1;
            if (!(SDL_HasIntersection(&newHitbox, &opponentHitbox)))
            {
                cooldown += 1;
                if (cooldown >= 2)
                {
                    hitbox.x -= 1;
                    cooldown = 0;
                }
            }
        }
    }
    else if (isHit)
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 hitDuration = currentTime - hitStartTime;
        if (hitDuration >= 200)
            isHit = false;
    }
    else
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 attackDuration = currentTime - attackStartTime;
        if (attackDuration >= 300)
            isAttack = false;
    }
    if (opponent.playerNum == 2)
        cooldown1 = cooldown;
    else
        cooldown2 = cooldown;
}

void PlayerCharacter::attackHandler(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent)
{
    if (isAttack)
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 attackDuration = currentTime - attackStartTime;
        if (attackDuration >= 300)
            isAttack = false;
    }
    else
    {
    
        if (pressedKeys.count(attackKey))
        {
            isAttack = true;
            attackStartTime = SDL_GetTicks();
            // Define the hitbox dimensions
            int hitboxWidth = 75;       //z - made hitbox bigger
            int hitboxHeight = 75;
            int side;

            if (playerNum == 1)
                side = 1;
            else   
                side = -1;
            // Calculate the hitbox position relative to the character's center right
            SDL_Rect attackHitbox = {
                hitbox.x + side * hitbox.w - side * 67,               // Right side of the character
                hitbox.y - (hitbox.h - hitboxHeight) / 2,  // Center vertically
                hitboxWidth,
                hitboxHeight
            };

            SDL_Rect opponentHitbox = opponent.getHitbox();
            // Check for intersection using local variables
            if (SDL_HasIntersection(&attackHitbox, &opponentHitbox)) 
            {
                // Deal damage to the opponent
                opponent.takeDamage(5);
            }
        }
    }
}

void PlayerCharacter::takeDamage(int damage)
{
    playerHealth.takeDamage(damage);
    isHit = true;
    hitStartTime = SDL_GetTicks();
}

bool PlayerCharacter::getMovingState(unordered_set<SDL_Keycode>& pressedKeys) {
    if (pressedKeys.count(leftKey) || pressedKeys.count(rightKey))
        return true;
    return false;
}

//g++ -g SDLHelper.cpp Character.cpp gameloop.cpp health.cpp PlayerCharacter.cpp MatchManager.cpp main2.cpp -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -w -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
