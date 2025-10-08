#pragma once
#include "StateCommand.hpp"
#include "Sprite.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

class RunningCommand : public StateCommand {
    
public:
    void update(Sprite* sprite) override;
    void setScreenWidth(float width) { screenWidth = width; };
    
protected:
    float screenWidth;
};
