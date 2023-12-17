#pragma once

#include <iostream>

class SkillBar { //we really wish we could implement this class + a couple classes for special moves, but the workload was just too much. apologies
private:
    int value;

public:
    SkillBar(int s);

    void displaySkillBar() const;
    void increaseSkill(int amount);
    void decreaseSkill(int amount);
};
