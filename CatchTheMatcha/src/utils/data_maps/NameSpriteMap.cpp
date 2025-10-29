#include <map>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "NameSpriteMap.hpp"
#include "../../../external/json/json.hpp"
// A mapping data structure. Given a NAME, maps to a sprite in the game. For reading in JSON's, the format should be:
/*
 "Name_1": {sprite_1 parameters},
 "Name_2": {...},
 ...
 */

Sprite* NameSpriteMap::getSprite(NAME name) {
    if (nameSpriteMap.count(name) == 0) {
        throw std::runtime_error("Key not found in name-sheet map.");
    } else {
        return nameSpriteMap[name];
    }
}

int NameSpriteMap::numSprites() {
    int counter = 0;
    for (auto& name : nameSpriteMap) {
        counter++;
    }
    return counter;
}

void NameSpriteMap::setSheetMapAll(NameStateSheetMap *sheetMap) {
    // recur thru all sprites and set their sheet map
    for (const auto& name : nameSpriteMap) {
        nameSpriteMap[name.first]->setSheetMap(sheetMap);
    }
}

void NameSpriteMap::addSprite(NAME name, Sprite* sprite) {
    // opt for this when the sprite is blank is not yet defined
    nameSpriteMap[name] = sprite;
}

void NameSpriteMap::addSprite(Sprite* sprite) {
    // well-defined sprite
    NAME name = sprite->getName();
    nameSpriteMap[name] = sprite;
}

void NameSpriteMap::loadJSON(std::string filepath) {
    // open file
    std::ifstream file(filepath);
    
    // Catch error
    if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
    
    // read in data from file
    nlohmann::json data;
    file >> data;
    file.close();
    
    // Recurring thru map
    int counter = 0;
    for (auto i = data["name_list"].begin(); i != data["name_list"].end(); i++) {
        // i returns key value pair
        std::string nameStr = (std::string) data["name_list"][counter];
        NAME name = strToNameMap[nameStr];
        // WARNING WITH USING NEW HERE
        Sprite* newSprite = new Sprite(name);
        nameSpriteMap[name] = newSprite;
        // done
        counter++;
    }
}


