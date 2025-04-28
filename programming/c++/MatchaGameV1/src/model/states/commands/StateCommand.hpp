#pragma once
#include <map>
#include <SDL3/SDL.h>

#include "Sprite.hpp"

class Sprite; // forward declaration

// A StateCommand functions as an abstract class for creating commands that update sprites based on their states.
// An instance of StateCommand cannot be created, but classes that inherit from it can.
// Virtual methods are defined/implemented by classes that inherit from StateCommand.

class StateCommand {
    
public:
    // given a sprite and input, mutate the sprite accordingly
    StateCommand();
    virtual ~StateCommand();
    virtual void update(Sprite* sprite);
};


