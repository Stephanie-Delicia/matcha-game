#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"

/*
 An abstract class that handles the sprite states.
 */

class SpriteState {
public:
    virtual void update(Sprite* sprite) = 0;
    virtual void draw(Sprite* sprite, SDL_Surface *windowSrfc) = 0;
    virtual void handleInput(Sprite* sprite, const SDL_Event &input) = 0;
};
