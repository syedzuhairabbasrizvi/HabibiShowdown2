#include "MatchManager.hpp"

//constructor implementation
MatchManager::MatchManager(const string initialState) : gameState(initialState) {}

//function to print the game state implementation, used for error checking
void MatchManager::printGameState() const 
{
    std::cout << "Current Game State: " << gameState << std::endl;
}
//following are self explanatory
string MatchManager::getGameState() const
{
    return gameState;
}

void MatchManager::setGameState(string newState)  
{
    gameState = newState;
}