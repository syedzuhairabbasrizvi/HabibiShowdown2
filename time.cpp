#include "time.hpp"

Time::Time(int h, int m) : hours(h), minutes(m) {}

void Time::displayTime() const {
    std::cout << hours << ":" << minutes;
}
