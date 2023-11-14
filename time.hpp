#pragma once

#include <iostream>

class Time {
private:
    int hours;
    int minutes;

public:
    Time(int h, int m);

    void displayTime() const;
};
