#pragma once
#include <map>
#include <SDL3/SDL.h>

#include "Sprite.hpp"
#include "StateCommand.hpp"
#include "SpriteState.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"

class Sprite;

/*
 An abstract class that handles the sprite states.
 */

class CharState : SpriteState {
public:
    CharState();
    ~CharState();
    void handleInput(Sprite* sprite, SDL_Event const &input);
    void update(Sprite* sprite);
    
    // static instances of commands for char characters
    static WalkingCommand walkingC;
    static IdleCommand idleC;
    
private:
    StateCommand currCommand = idleC;
};
