#include "MainSprite.hpp"
#include <map>
#include <iostream>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteStruct.hpp"
#include "SpriteSheet.hpp"
#include "sdl_rect_utils.h"
#include "CharacterState.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game. Contains information such as name, location, and states such as direction the char is facing.
 */

void MainSprite::addState(STATE s) {
    statesToProcess.push_back(s);
}

void MainSprite::clearQueue() {
    statesToProcess.clear();
}

void MainSprite::removeState(STATE s) {
    // if found, object is removed
    auto find_iterator = std::find(statesToProcess.begin(), statesToProcess.end(), s);
    if (find_iterator != statesToProcess.end()) {
        statesToProcess.erase(find_iterator);
    }
}
