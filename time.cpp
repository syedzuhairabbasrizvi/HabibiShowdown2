#include "time.hpp"
#include <iostream>
#include <SDL.h>

//constructor
Time::Time() : startTime(0), currentTime(0), isRunning(false) {}

void Time::startTimer() {
    startTime = SDL_GetTicks(); //get current time in millisec
    isRunning = true;
}

//caluculating elapsed time
void Time::updateTimer() {
    if (isRunning) {
        currentTime = (SDL_GetTicks() - startTime) / 1000; // Convert milliseconds to seconds
    }
}

void Time::displayTime() const {
    if (isRunning) {
        int seconds = currentTime % 60;
        int minutes = (currentTime / 60) % 60;
        int hours = currentTime / 3600;
        std::cout << hours << ":" << minutes << ":" << seconds << std::endl;
    }
}

//checking if limit is reached
bool Time::isTimeUp(int limitInSeconds) {
    return currentTime >= limitInSeconds;
}

void Time::stopTimer() {
    isRunning = false;
}

