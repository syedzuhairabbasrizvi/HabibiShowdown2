#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <unordered_set>
#include "animator.hpp"

using namespace std;

class Character {
public:
    std::string name;
    int health;
    int skillBar;
    bool isJumping; // New variable to track the jumping state
    int jumpStartTime;
    bool isAttack;
    int attackStartTime;
    bool isHit;
    int hitStartTime;
    SDL_Rect hitbox;
    Animator neutralAnimator;

public:
    // constructor
    Character(string n, int h, int s, SDL_Rect hb);

    void storeNeutralFrame(SDL_Texture* frame);

    bool getJumpState();

    bool getAttackState();

    // attack func
    void attack();

    // special move func
    void specialMove();

    // defend func
    void defend();

    SDL_Rect getHitbox() const;

};
