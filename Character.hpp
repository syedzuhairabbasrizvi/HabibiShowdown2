#pragma once

#include <iostream>
#include <string>

class Character {
private:
    string name;
    int health;
    int skillBar;

public:
    // constructor
    Character(string n, int h, int s);

    // movement func
    void move();

    // attack func
    void attack();

    // special move func
    void specialMove();

    // defend func
    void defend();
};
