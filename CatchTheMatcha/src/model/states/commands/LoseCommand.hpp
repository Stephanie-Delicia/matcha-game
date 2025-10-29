#pragma once
#include "StateCommand.hpp"
/*
 A class representing the command for handling the walking state for a sprite.
 */

class LoseCommand : public StateCommand {
    
public:
    LoseCommand() {};
    void update(Sprite* sprite) override;
    void setTimer(Timer* t)   { timer = t; };
    void resetAnimDuration()  { animDuration = 0; };
    void setShiftDone(bool b) { initialShiftDone = b; };
    
protected:
    Timer* timer;
    float startTime = 0;
    float timeElapsed = 0;
    float animDuration = 1000; // time that animation plays out, in ms
    bool initialShiftDone = false; // needed for the first instance of this state being drawn
};
