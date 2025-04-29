#pragma once
#include <map>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"
#include "STATE.h"

/*
 An abstract class that handles the sprite states.
 */

class CharacterState : SpriteState {
public:
    void handleInput(Sprite* sprite, SDL_Event const &input);
    void update(Sprite* sprite);
    
private:
    STATE currState = NONE;
    // static instances of commands for char characters
    IdleCommand idleC = IdleCommand();
    WalkingCommand walkingC = WalkingCommand();
};
