#pragma once
#include <map>
#include <deque>
#include <tuple>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "Sprite.hpp"
#include "SpriteStruct.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"

// use a forward declaration instead
class SpriteState;

/*
 A class representing a sprite (char, background texture, etc) in the game.
 Contains information such as name, location, and states such as direction the char is facing.
 */

class MainSprite : public Sprite {
public:
    // instead of using the singular STATE, we will have a queue to fulfill to handle more complex series of
    // keyboard inputs.
    void addState(STATE s);
    void removeState(STATE s);
    void clearQueue();
    
    // getters
    std::deque<STATE> getStates() { return statesToProcess; } ;
    
protected:
    std::deque<STATE> statesToProcess;
};
