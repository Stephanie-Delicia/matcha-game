/*
 A class representing the command for handling the idle state for a sprite.
 */
#pragma once
#include "StateCommand.hpp"
#include "Sprite.hpp"

class IdleCommand : public StateCommand {
    
public:
    IdleCommand() {};
    void update(Sprite* sprite);
};
