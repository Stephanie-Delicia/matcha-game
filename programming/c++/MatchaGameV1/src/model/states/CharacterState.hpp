/*
 A concrete class that handles the states of a character sprite (one that can be moved with keyboard arrows).
 */
#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"

class CharacterState : public SpriteState {
public:
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);
    
private:
    // commands
    IdleCommand idleC = IdleCommand();
    WalkingCommand walkingC = WalkingCommand();
};
