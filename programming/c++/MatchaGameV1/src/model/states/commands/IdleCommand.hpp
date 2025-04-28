#pragma once
#include <map>
#include <SDL3/SDL.h>

#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"

#include "Posn.hpp"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"

/*
 A class representing the command for handling the idle state for a sprite.
 */

class IdleCommand : public StateCommand {
    
public:
    IdleCommand();
    ~IdleCommand();
    void update(Sprite* sprite);
};
