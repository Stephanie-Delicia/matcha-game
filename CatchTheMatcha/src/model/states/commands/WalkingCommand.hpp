#pragma once
#include "StateCommand.hpp"
/*
 A class representing the command for handling the walking state for a sprite.
 */

class WalkingCommand : public StateCommand {
    
public:
    WalkingCommand() {};
    void update(Sprite* sprite) override;
    void setScreenWidth(float width) { screenWidth = width; };
    
protected:
    float screenWidth;
};
