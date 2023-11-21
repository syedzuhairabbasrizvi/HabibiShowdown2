#include "Character.hpp"

Character::Character(std::string n, int h, int s) : name(n), health(h), skillBar(s), isJumping(false), jumpStartTime(0) {}

// Add this to your character.cpp file
void Character::move(SDL_Rect& characterRect, unordered_set<SDL_Keycode>& pressedKeys, int playerNumber) {
    // Adjust keys based on player number
    SDL_Keycode rightKey, leftKey, upKey;

    if (playerNumber == 1) {
        rightKey = SDLK_RIGHT;
        leftKey = SDLK_LEFT;
        upKey = SDLK_UP;
    } else if (playerNumber == 2) {
        rightKey = SDLK_d;
        leftKey = SDLK_a;
        upKey = SDLK_w;
    } else {
        // Handle an invalid player number (optional)
        return;
    }

    // Jump action
    if (pressedKeys.count(upKey) && !isJumping) {
        // If the Up key is pressed and the player is not already jumping
        isJumping = true;
        jumpStartTime = SDL_GetTicks();  // Record the start time of the jump

    }

    // Simulate character movement based on keyboard input
    if (pressedKeys.count(rightKey)) {
        characterRect.x += 10;
    }

    if (pressedKeys.count(leftKey)) {
        characterRect.x -= 10;
    }


}

bool Character::getJumpState() {
    return isJumping;
}

void Character::gravity(SDL_Rect& characterRect) {
    if (isJumping){
        Uint32 currentTime = SDL_GetTicks();
        Uint32 jumpDuration = currentTime - jumpStartTime;

        // Adjust the jump duration and gravity speed based on your preferences
        if (jumpDuration < 250) {  // Adjust the jump duration (milliseconds)
            characterRect.y -= 1;  // Adjust the jump height
        } else {
            // Apply gravity after the jump duration
            characterRect.y += 1;  // Adjust the gravity speed
        }

        // Check if the player has reached the ground
        if (characterRect.y >= 500) { // Adjust the ground level as needed
            characterRect.y = 500; // Set the player back to the ground
            isJumping = false; // Reset the jumping state
        }
    }
}

void Character::attack() {
    // press spacebar
    std::cout << "Attacking" << std::endl;
    // target takes damage if direct hit; according to the degree of hit
}

void Character::specialMove() {
    // press x
    std::cout << "Special move activated" << std::endl;
    // target takes damage if a direct hit; according to the degree of hit
}

void Character::defend() {
    // press ctrl+d
    std::cout << "Shield deployed" << std::endl;
    // prevent damage
}
