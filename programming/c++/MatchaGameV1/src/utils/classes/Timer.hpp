#pragma once
#include <cstdint>
// A class for a timer for a game. Time is in seconds.
// Written using https://lazyfoo.net/tutorials/SDL/23_advanced_timers/index.php

class Timer {
public:
    Timer() {
        startTime = 0;
        pausedTime = 0;
        paused = false;
        started = false;
    };
    
    void start(); // starts timer
    void stop();
    void pause();
    void unpause();
    
    // get time
    float getTicks();
    
    // check timer
    bool isStarted();
    bool isPaused();
    
private:
    // running duration
    float startTime;

    // pause duration
    float pausedTime;

    // timer status
    bool paused;
    bool started;
};
