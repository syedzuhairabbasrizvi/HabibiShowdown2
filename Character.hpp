#pragma once

#include <iostream>
#include <string>
#include <unordered_set>
#include <SDL.h>

using namespace std;

class Character {
private:
    std::string name;
    int health;
    int skillBar;
    bool isJumping; // New variable to track the jumping state
    int jumpStartTime;

public:
    // constructor
    Character(string n, int h, int s);

    // movement func
    void move(SDL_Rect& characterRect, unordered_set<SDL_Keycode>& pressedKeys,int playerNumber);

    bool getJumpState();

    void gravity(SDL_Rect& characterRect);

    // attack func
    void attack();

    // special move func
    void specialMove();

    // defend func
    void defend();
};
