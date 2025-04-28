#pragma once
#include <map>
#include <SDL3/SDL.h>

#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"

#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

class WalkingCommand : public StateCommand {
    
public:
    WalkingCommand();
    ~WalkingCommand();
    // void handleInput(Sprite* sprite, SDL_Event const &input);
    void update(Sprite* sprite);
};
