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
    // constructors
    NameSpriteMap() {
        nameSpriteMap = {};
    };
    
    NameSpriteMap(std::map<std::string, NAME> strMap) {
        strToNameMap = strMap;
    };
    
    // adders
    void addSprite(Sprite* sprite);            // add a well-define sprite
    void addSprite(NAME name, Sprite* sprite); // add a blank sprite
    
    // getters
    Sprite* getSprite(NAME name);
    
    // setters
    void setSheetMapAll(NameStateSheetMap* sheetMap);
    
    // info functions
    int numSprites();
    
    // JSON loading
    void loadJSON(std::string filepath);
    
private:
    std::map<NAME, Sprite*> nameSpriteMap;
    std::map<std::string, NAME> strToNameMap = {
        {"winnie", WINNIE},
        {"pleasant_sky", PLEASANT_SKY},
        {"test_box", TEST_BOX},
        {"start_button_test", START_BUTTON_TEST},
        {"start_screen_test", START_SCREEN_TEST}
    };
};
