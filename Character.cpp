#include "Character.hpp"

Character::Character(std::string n, int h, int s, SDL_Rect hb) : name(n), health(h), skillBar(s), isJumping(false), isAttack(false),isHit(false), hitStartTime(0), jumpStartTime(0), attackStartTime(0), hitbox(hb) {}

// Add this to your character.cpp file


void Character::storeNeutralFrame(SDL_Texture* frame)
{
    neutralAnimator.pushFrame(frame);
}


bool Character::getJumpState() {
    return isJumping;
}

bool Character::getAttackState() {
    return isAttack;
}

SDL_Rect Character::getHitbox() const {
    // Return the hitbox of the character
    return hitbox; // Replace with the actual representation of your character
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


