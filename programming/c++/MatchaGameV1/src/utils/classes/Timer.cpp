#include <SDL3/SDL.h>
#include "Timer.hpp"
#include <cstdint>

bool Timer::isStarted() {
    return started; // timer started
}

bool Timer::isPaused() {
    return paused && started; // check if timer is paused
}

void Timer::start() {
    started = true; // start timer
    paused = false; // pause timer
    
    pausedTime = 0;
    startTime = SDL_GetTicks(); // get current time
}

void Timer::stop() {
    paused = false;
    started = false;
    
    startTime = 0;
    pausedTime = 0;
}

void Timer::pause() {
    // if the timer is running and isn't paused
    if (started && !paused) {
        paused = true;                           // pause
        pausedTime = SDL_GetTicks() - startTime; // total pause time
        startTime = 0;                           // restart
    }
}

void Timer::unpause() {
    // if the timer is running and paused
    if (started && paused) {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTime = static_cast<float>(SDL_GetTicks()) - pausedTime;

        //Reset the paused ticks
        pausedTime = 0;
    }
}

float Timer::getTicks() {
    std::uint64_t time = 0;
    
    if (started) { // if timer is running
        if (paused) { // if the timer is paused
            time = pausedTime; // return paused time
        }
        else {
            time = SDL_GetTicks() - startTime;  // return time running unpaused
        }
    }
    return time;
}
