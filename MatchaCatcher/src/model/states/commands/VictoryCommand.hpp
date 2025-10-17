#pragma once
#include "StateCommand.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

class VictoryCommand : public StateCommand {
    
public:
    VictoryCommand() {};
    void update(Sprite* sprite) override;
    void setTimer(Timer* t) { timer = t; };
    void resetAnimDuration() { animDuration = 0; };
    
protected:
    float startTime = 0;
    float timeElapsed = 0;
    Timer* timer;
    
    float animDuration = 1000; // time that animation plays out, in ms
};
