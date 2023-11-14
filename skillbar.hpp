#pragma once

#include <iostream>

class SkillBar {
private:
    int value;

public:
    SkillBar(int s);

    void displaySkillBar() const;
    void increaseSkill(int amount);
    void decreaseSkill(int amount);
};
