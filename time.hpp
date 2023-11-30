#ifndef TIME_HPP
#define TIME_HPP

class Time {
public:
    Time();
    void startTimer();
    void updateTimer();
    void displayTime() const;
    bool isTimeUp(int limitInSeconds);
    void stopTimer();

private:
    unsigned int startTime;
    unsigned int currentTime;
    bool isRunning;
};

#endif
