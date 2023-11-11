#include "MatchManager.hpp"

// Constructor implementation
MatchManager::MatchManager(const string initialState) : gameState(initialState) {}

// Function to print the game state implementation
void MatchManager::printGameState() const 
{
    std::cout << "Current Game State: " << gameState << std::endl;
}