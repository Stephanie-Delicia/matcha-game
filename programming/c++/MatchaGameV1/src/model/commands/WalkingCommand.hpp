#pragma once
#include <map>
#include <SDL3/SDL.h>
#include "StateCommand.hpp"
#include "Sprite.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

class WalkingCommand : public StateCommand {
    
public:
//    WalkingCommand();
//    ~WalkingCommand();
    void update(Sprite* sprite) override;
};
