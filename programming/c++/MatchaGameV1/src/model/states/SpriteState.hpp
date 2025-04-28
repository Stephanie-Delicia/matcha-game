#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "StateCommand.hpp"

/*
 An abstract class that handles the sprite states.
 */

class Sprite;

class SpriteState {
    
public:
    SpriteState();
    virtual ~SpriteState();
    virtual void handleInput(Sprite* sprite, SDL_Event const &input);
    virtual void update(Sprite* sprite);
};
