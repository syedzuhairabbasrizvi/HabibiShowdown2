#include "character.hpp"

Character::Character(std::string n, int h, int s) : name(n), health(h), skillBar(s) {}

void Character::move() {
    // press right
    std::cout << "Moving right" << std::endl;

    // press left
    std::cout << "Moving left" << std::endl;

    // press up
    std::cout << "Jumping" << std::endl;

    // press down
    std::cout << "Ducking" << std::endl;
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
