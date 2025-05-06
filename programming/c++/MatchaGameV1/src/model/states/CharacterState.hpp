#pragma once
#include <map>
#include <tuple>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "SpriteStruct.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"
#include "STATE.h"

/*
 An abstract class that handles the sprite states.
 */

class CharacterState : SpriteState {
public:
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);
    
private:
    // commands
    IdleCommand idleC = IdleCommand();
    WalkingCommand walkingC = WalkingCommand();
};
