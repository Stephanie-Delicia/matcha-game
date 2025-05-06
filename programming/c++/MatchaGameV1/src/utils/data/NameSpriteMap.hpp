#pragma once
#include <stdio.h>
#include "NAME.h"
#include "STATE.h"
#include "Sprite.hpp"
#include "DIRECTION.h"
#include "SpriteSheet.hpp"
#include <map>
#include <string>
#include "NameStateSheetMap.hpp"

// A mapping data structure. Given a NAME, maps to a sprite in the game. For reading in JSON's, the format should be:
/*
 "Name_1": {sprite_1 parameters},
 "Name_2": {...},
 ...
 */

class NameSpriteMap {
public:
    // constructor/destructor
    NameSpriteMap() {
        nameStrMap = {
            {"Winnie", WINNIE}};
    };
    
    // utils
    Sprite* getSprite(NAME name);                     // returns sprite
    void readJSON(std::string filepath);              // add sprite sheets according to json file
    void addSprite(NAME name, Sprite* sprite);        // add a sprite sheet
    void setSheetMapAll(NameStateSheetMap* sheetMap); // for all sprites, make this the sheet map
    
private:
    std::map<NAME, Sprite*> nameSpriteMap;
    std::map<std::string, NAME> nameStrMap;
};
