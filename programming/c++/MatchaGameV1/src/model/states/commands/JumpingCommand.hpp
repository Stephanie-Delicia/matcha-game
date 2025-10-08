#pragma once
#include "Sprite.hpp"
#include "Timer.hpp"
#include "StateCommand.hpp"

/*
 A class representing the command for handling the jumpinh state for a sprite.
 Need to know the floor to know when the command ends.
 */

class JumpingCommand : public StateCommand {
    
public:
    void update(Sprite* sprite) override;
    
    // setters
    void setScreenWidth(float width) { screenWidth = width; };
    void setScreenFloor(float floor) { screenFloor = floor; };
    void setTimer(Timer* t) { timer = t; };
    void setAccDueToG(float g) { accDueToG = g; };
    void setInitV(float v) { initV = v; };
    void setDone(bool b) {isDone = b;};
   
    // info
    float getJumpDuration() { return (-initV * (2.00/accDueToG)); };
    bool getIsDone() { return isDone; };
   
    // updates
    void updateV(float changeInTime) { currV = currV - (changeInTime * accDueToG); };
    
protected:
    // VELOCITY HERE IS REFERRING TO THE Y-VELOCITY, X-VELOCITY SHOULD STAY CONSTANT AND IS
    // SPRITE CLASS INFO.
    bool isDone = false;
    float initV = -75.00;
    float currV = -75.00;
    float accDueToG = 300; // acceleration due to gravity, i'll have this be something that can be changed
    float screenWidth;
    float screenFloor = 267.00;
    Timer* timer;
    float startTime = 0;
    float timeElapsed = 0;
};
