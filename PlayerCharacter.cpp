#include "playercharacter.hpp"

PlayerCharacter::PlayerCharacter(std::string n, int h, int s, std::string pN, int pNo)
    : Character(n, h, s), playerName(pN), playerNo(pNo) {}

void PlayerCharacter::InputProcessor() {
    // enter inputs
    std::cin >> leftCont;
    std::cin >> rightCont;
    std::cin >> upCont;
    std::cin >> downCont;
    std::cin >> attackCont;
    std::cin >> specialMoveCont;
    std::cin >> defendCont;
}
