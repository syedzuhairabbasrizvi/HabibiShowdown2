#include "PlayerCharacter.hpp"

#include <iostream>

bool PlayerCharacter::gameOver = false;

PlayerCharacter::PlayerCharacter(std::string n, int h, int s, int playerNumber, SDL_Rect hb, bool d) : Character(n, h, s, hb) , playerHealth(h), speed(2.5), direction(d) {

    playerNum=playerNumber; //iori is player 1, kyo is player 2

    if (playerNumber == 2) { //kyo works with arrow keys
        rightKey = SDLK_RIGHT;
        leftKey = SDLK_LEFT;
        upKey = SDLK_UP;
        attackKey = SDLK_KP_1;
    } else if (playerNumber == 1) { //iori works with wasd
        rightKey = SDLK_d;
        leftKey = SDLK_a;
        upKey = SDLK_w;
        attackKey = SDLK_j;
    } 
}

void PlayerCharacter::renderHealth(SDL_Renderer* renderer)
{
    playerHealth.healthbar(renderer, 85 + (370*(playerNum-1)), 60, 260, 16, {255, 0, 0, 255}, {0, 255, 0, 255}, playerNum); //sending required attributes to the health bar rendering function, there is an eyeballed calculation here on x position depending on player position
}

void PlayerCharacter::gravity(PlayerCharacter& opponent) {
    int static cooldown1 = 0; //we are calling ths function many times, during which our cooldown should continue from where it left off!
    int static cooldown2 = 0;
    int cooldown;
    if (opponent.playerNum == 2) //this was done earlier on when the code wasnt as object oriented as it was now. i dont want to touch it
        cooldown = cooldown1;
    else
        cooldown = cooldown2;
    if (isJumping){ //if we are already jumping, do the following
        Uint32 currentTime = SDL_GetTicks(); //our earlier system was time oriented. that didnt work out well though so thats what this is for
        Uint32 jumpDuration = currentTime - jumpStartTime;
        cooldown += 1; //increment cooldown every time function is called
        if (speed == 2.5) //this is an initializer for the isUp flag
            isUp = true;
        //adjust the jump duration and gravity speed based on your preferences
        if (speed>=0 && isUp == true)  //we are currently moving up and have not reached the peak
        {  //adjust the jump duration (milliseconds)
            if (cooldown >= 3) //this cooldown is to ensure our process doesnt occur too fast
            {
                cooldown = 0;
                hitbox.y -= speed;
                speed -= 0.02; //this way, our deceleration is constant and the speed smoothly decreases. similar to real life gravity!
            }
        } 
        else 
        {
            if (isUp==true) 
                speed = 0;
            isUp = false;
            SDL_Rect opponentHitbox = opponent.getHitbox();
            SDL_Rect newHitbox = hitbox; //this new hitbox is smaller than the hitbox of the player so that we can allow the characters to be close together at most
            newHitbox.w -= 50;
            newHitbox.h -= 100;
            if (cooldown >= 3)
            {
                newHitbox.y += speed; //similar as above
            }
            if ((SDL_HasIntersection(&newHitbox, &opponentHitbox))) //to avoid collision while jumping!
            {
                if (direction) 
                    hitbox.x -=10; //if we are facing one way, set them down beside the opponent in a way that maintains the original direction
                else
                    hitbox.x +=10;
            }
            //apply gravity after the jump duration
            if (cooldown >= 3)
            {
                cooldown = 0;
                hitbox.y += speed ;  //adjust the gravity speed
                speed += 0.02;
            }
        }

        //check if the player has reached  ground
        if (hitbox.y >= floor) { //adjust the ground level as needed
            hitbox.y = floor; //set the player back to the ground
            speed = 2.5;
            isJumping = false; //reset the jumping state
        }
    }
    if (opponent.playerNum == 2) //updating cooldown
        cooldown1 = cooldown;
    else
        cooldown2 = cooldown;
}


void PlayerCharacter::handleDirection(PlayerCharacter& opponent)
{
    if (!isJumping)
        direction = hitbox.x < (opponent.getHitbox()).x; //comparing hitbox x values to ensure we are facing the right way
}


void PlayerCharacter::move(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent) {
    //adjust keys based on player number
    int static cooldown1 = 0;
    int static cooldown2 = 0;
    int cooldown;
    if (opponent.playerNum == 2)
        cooldown = cooldown1;
    else
        cooldown = cooldown2;
    if (!(isHit || isAttack))
    {
        //inside the move function of PlayerCharacter
        SDL_Rect opponentHitbox = opponent.getHitbox();
        //jump action
        if (pressedKeys.count(upKey) && !isJumping && !gameOver) {
            //if the Up key is pressed and the player is not already jumping
            isJumping = true;
            jumpStartTime = SDL_GetTicks();  //record the start time of the jump

        }

        //simulate character movement based on keyboard input
        if (pressedKeys.count(rightKey) && hitbox.x <= 670 && !gameOver) { //not 800 because i have to account for character width as well
            SDL_Rect newHitbox = hitbox;
            newHitbox.x += 51;
            newHitbox.w -= 50;
            if (isJumping)
                newHitbox.y -= 100;
            if (!(SDL_HasIntersection(&newHitbox, &opponentHitbox))||!direction) //either we are present on left side and colliding, or present on right side in which case collision isnt important
            {
                cooldown += 1;
                if (cooldown >= 4)
                {
                    if (direction) //walking forwards speed is double walking backwards speed
                    {
                        hitbox.x += 2;
                        forwards = true;
                    }
                    else
                    {
                        hitbox.x += 1;
                        forwards = false;
                    }
                    cooldown = 0;
                }
            }
        }

        if (pressedKeys.count(leftKey)  && hitbox.x >= 0 && !gameOver) 
        {
            SDL_Rect newHitbox = hitbox;
            newHitbox.x += 49;
            newHitbox.w -= 50;
            if (isJumping)
                newHitbox.y -= 100;
            if (!(SDL_HasIntersection(&newHitbox, &opponentHitbox))||direction) //above case but for opposite direction
            {
                cooldown += 1;
                if (cooldown >= 4)
                {
                    if (direction)
                    {
                        hitbox.x -= 1;
                        forwards = false;
                    }
                    else
                    {
                        hitbox.x -= 2;
                        forwards = true;
                    }
                    cooldown = 0;
                }
            }
        }
    }
    else if (isHit) //we cannot move if we are hit! so we must recover first
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 hitDuration = currentTime - hitStartTime;
        if (!hitAnimator.isOn())
            isHit = false;
    }
    if (opponent.playerNum == 2) //similar to previous function
        cooldown1 = cooldown;
    else
        cooldown2 = cooldown;
}

void PlayerCharacter::attackHandler(unordered_set<SDL_Keycode>& pressedKeys, PlayerCharacter& opponent)
{
    if (isAttack) //go through the entire attack animation if we are attacking!
    {
        Uint32 currentTime = SDL_GetTicks();
        Uint32 attackDuration = currentTime - attackStartTime;
        if (!punchAnimator.isOn())
            isAttack = false;
    }
    else if (isHit != true)
    {
        if (pressedKeys.count(attackKey) && !isJumping && !gameOver)
        {
            isAttack = true;
            attackStartTime = SDL_GetTicks();
            //define the hitbox dimensions
            int hitboxWidth = 75;
            int hitboxHeight = 75;
            
            //calculate the hitbox position based on character direction
            int attackX = direction ? hitbox.x + 120 : hitbox.x;
            


            SDL_Rect attackHitbox = {
                attackX,
                hitbox.y,
                hitboxWidth,
                hitboxHeight
            };

            channel1 = Mix_PlayChannel(-1,punchSound,0); //we need a separate channel if we want to play a sound on top of background music, so that is done here

            SDL_Rect opponentHitbox = opponent.getHitbox();

            //check for intersection using local variables
            if (SDL_HasIntersection(&attackHitbox, &opponentHitbox)) 
            {
                //deal damage to the opponent
                opponent.takeDamage(10);
            }
        }
    }
}

void PlayerCharacter::takeDamage(int damage)
{
    
    playerHealth-=damage;
    if (playerHealth > 0)
    {
        isHit = true;
        channel2 = Mix_PlayChannel(-1,hitSound,0); //oof ouchies i got hit :(
        
    }
    else
    {
        Mix_HaltMusic(); //shiver in the ice of the silence
        Mix_PlayMusic(deathSound, 0);
        isDefeated = true; //noooo its over. khallaas
        gameOver = true;
    }
    hitStartTime = SDL_GetTicks();
}

bool PlayerCharacter::getMovingState(unordered_set<SDL_Keycode>& pressedKeys) {
    if ((pressedKeys.count(leftKey) || pressedKeys.count(rightKey)) && !gameOver) //we are moving if the game is running and left or right key is pressed
        return true;
    return false;
}

bool PlayerCharacter::facingForwards()
{
    return forwards; //we are facing right
}

void PlayerCharacter::display(SDL_Renderer* renderer, SDL_Rect& rect, std::unordered_set<SDL_Keycode>& pressedKeys)
{
    if (direction) //flip the script if we are facing a certain direction
        SDL_RenderCopyEx(renderer, currentTexture, NULL, &rect, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    else //else deal as normal
        SDL_RenderCopy(renderer, currentTexture, nullptr, &rect);
}

int PlayerCharacter::getHealth() const {
    return playerHealth.getHealth();
}

bool PlayerCharacter::isGameOver() const
{
    return gameOver;
}

void PlayerCharacter::setGameRun()
{
    gameOver = false;
}
