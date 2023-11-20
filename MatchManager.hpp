#pragma once

#include <iostream>
#include <string>

using namespace std;

class MatchManager {
private:
    string gameState;

public:
    // Constructor
    MatchManager(const string initialState);

    // Function to print the game state
    void printGameState() const;
    void setGameState(string newState);
    string getGameState() const;
};

