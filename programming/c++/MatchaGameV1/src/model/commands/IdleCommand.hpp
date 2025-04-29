#pragma once
#include <map>
#include <SDL3/SDL.h>
#include "StateCommand.hpp"
#include "Sprite.hpp"

/*
 A class representing the command for handling the idle state for a sprite.
 */

class IdleCommand : public StateCommand {
    
public:
//    IdleCommand();
//    ~IdleCommand();
    void update(Sprite* sprite);
};
