#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"

/*
 An abstract class that handles the sprite states.
 */

class SpriteState {
public:
    // virtual ~SpriteState();
    virtual void handleInput(Sprite* sprite, SDL_Event const &input) = 0;
    virtual void update(Sprite* sprite) = 0;
};
