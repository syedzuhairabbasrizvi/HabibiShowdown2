#pragma once

#include <iostream>
#include <string>

class Character {
private:
    std::string name;
    int health;
    int skillBar;

public:
    // constructor
    Character(std::string n, int h, int s);

    // movement func
    void move();

    // attack func
    void attack();

    // special move func
    void specialMove();

    // defend func
    void defend();
};
