#pragma once
#include "StateCommand.hpp"
#include "Sprite.hpp"
#include "Posn.hpp"
#include <deque>
#include <tuple>
#include "STATE.h"
#include "Timer.hpp"
#include "DIRECTION.h"

/*
 A class representing the command for handling the walking state for a sprite.
 */

class SpeedBoostCommand : public StateCommand {
    
public:
    void update(Sprite* sprite) override;
    std::deque<std::tuple<Posn, STATE, DIRECTION>> getImages() {return images;};
    void setImages(std::deque<std::tuple<Posn, STATE, DIRECTION>> posns) {images = posns;};
    
    void addTuple(Sprite* sprite);
    void setTimer(Timer* t)        { timer = t; };
    void setMaxNumImages(int num)  { maxNumImages = num; };
    void resetBoostDuration()      { boostDuration = 0; };
    void resetLastImageTime()      { lastImageTime = 0; };
    void setIsSpeedBoosted(bool b) { isSpeedBoosted = b; };
    bool getIsDone() { return isDone; };
    float getSpeedBoost() { return speedBoost; };
    void setStateDone(bool b) {isDone = b;};
    
    void resetSpeedBoostCommand(Sprite* sprite);
    
protected:
    bool isDone = false;
    bool isSpeedBoosted = false;
    // we need the list of posns and max num of images
    std::deque<std::tuple<Posn, STATE, DIRECTION>> images;
    
    // timer stuff
    Timer* timer;
    float speedBoost = 3;
    float startTime = 0;
    float timeElapsed = 0;
    float maxNumImages = 6;
    float boostDuration = 5000; // time that animation plays out, in ms
    float lastImageTime = 0; // 500 ms
    float timeBetweenImage = 30; // 500 ms
};
