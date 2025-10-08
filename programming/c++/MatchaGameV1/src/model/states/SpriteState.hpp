#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"

/*
 An abstract class that handles the sprite states. Has abstract method to implement, such as updating the sprite,
 drawing it, and handling game event inputs.
 */

class SpriteState {
public:
    virtual void update(Sprite* sprite) = 0;
    virtual void draw(Sprite* sprite, SDL_Surface *windowSrfc) = 0;
    virtual void handleInput(Sprite* sprite, const SDL_Event &input) = 0;
    virtual void resetCommands(Sprite* sprite) {}; // can be overriden. derived classes are not forced to implement this.
    
    // the difference between a virtual void func() = 0; and a virtual void func() {}; is in what you;re forced to do
    // essentially, for the first, you have a stronger contract in that derived classes MUST have their unique implementations.
    // The first example is what is referred to as 'interfaces', like in Java! They're very similar.
    // The second example, we have a lot of freedom since we provide an implementation already.
};
