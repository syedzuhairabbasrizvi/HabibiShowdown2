#include "skillbar.hpp"

SkillBar::SkillBar(int s) : value(s) {}

void SkillBar::displaySkillBar() const { //this class is very arbitrary
    std::cout << "Skill Bar: " << value << "\n";
}

void SkillBar::increaseSkill(int amount) {
    value += amount;
}

void SkillBar::decreaseSkill(int amount) {
    value -= amount;
    if (value < 0) {
        value = 0;
    }
}
