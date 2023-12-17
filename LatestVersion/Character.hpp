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
    bool isJumping; 
    bool isUp;
    int jumpStartTime;
    bool isAttack;
    int attackStartTime;
    bool isHit;
    bool isDefeated;
    int hitStartTime;
    int floor;
    SDL_Rect hitbox;
    Animator neutralAnimator;
    Animator moveAnimator;
    Animator backAnimator;
    Animator punchAnimator;
    Animator hitAnimator;
    Animator defeatAnimator;


public:
    // constructor
    Character(string n, int h, int s, SDL_Rect hb);

    void storeNeutralFrame(SDL_Texture* frame);

    void storeMoveFrame(SDL_Texture* frame);

    void storeBackFrame(SDL_Texture* frame); 

    void storePunchFrame(SDL_Texture* frame);

    void storeHitFrame(SDL_Texture* frame);

    void storeDefeatFrame(SDL_Texture* frame);


    bool getJumpState();

    bool getUpState();

    bool getAttackState();

    bool getHitState();

    bool getDefeatState();

    // attack func
    void attack();

    // special move func
    void specialMove();

    // defend func
    void defend();

    SDL_Rect getHitbox() const;

};
