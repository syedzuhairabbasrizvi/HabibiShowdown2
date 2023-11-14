#include "health.hpp"

Health::Health(int h) : value(h) {}

void Health::displayHealth() const {
    std::cout << "Health: " << value << "\n";
}

void Health::takeDamage(int damage) {
    value -= damage;
    if (value < 0) {
        value = 0;
        std::cout << "Try Again! You lost.";
    }
  if (value < 10) {
    std::cout << "WARNING:LOW HEALTH!";
  }
  //if other player's value = 0; you won
  //
}
