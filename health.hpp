#pragma once

#include <iostream>

class Health {
private:
    int value;

public:
    Health(int h);

    void displayHealth() const;
    void takeDamage(int damage);
};
