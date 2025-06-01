/*
 A concrete class that handles the states of a sprite that is falling and meant to be catched.
 */
#pragma once
#include "Posn.hpp"
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "TranslateCommand.hpp"

class BoxToCatchState : public SpriteState {
public:
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);
    
private:
    // command
    TranslateCommand transC = TranslateCommand();
};
