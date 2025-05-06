#include <stdio.h>
#include "NAME.h"
#include "STATE.h"
#include "Sprite.hpp"
#include "DIRECTION.h"
#include "SpriteSheet.hpp"
#include <map>
#include <string>
#include "NameSpriteMap.hpp"

// A mapping data structure. Given a NAME, maps to a sprite in the game. For reading in JSON's, the format should be:
/*
 "Name_1": {sprite_1 parameters},
 "Name_2": {...},
 ...
 */

Sprite* NameSpriteMap::getSprite(NAME name) {
    return nameSpriteMap[name];
}

void NameSpriteMap::setSheetMapAll(<#NameStateSheetMap *sheetMap#>) {
    
}

void NameSpriteMap::addSprite(NAME name, Sprite *sprite) {
    nameSpriteMap[name] = sprite;
}

void NameSpriteMap::readJSON(std::string filepath) {
    
}


