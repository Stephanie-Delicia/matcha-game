// A mapping data structure that refers to Name, then state, then finally the sheet pointer value.

#include "NameStateSheetMap.hpp"
#include <stdio.h>
#include "NAME.h"
#include "STATE.h"
#include "DIRECTION.h"
#include "SpriteSheet.hpp"
#include <map>
#include <fstream>
#include <iostream>
#include <fstream>
#include <string>
#include "json.hpp"

void NameStateSheetMap::addSpriteSheet(NAME name, STATE state, SpriteSheet* sheet) {
    nameStateSheetMap[name][state] = sheet;
}

SpriteSheet* NameStateSheetMap::getSpriteSheet(NAME name, STATE state) {
    // error if value does not exist
    // find name
    std::cout << "getSpriteSheet call. [NameStateSheetMap]\n";
    std::map<STATE, SpriteSheet*> stateSheetMap = nameStateSheetMap.at(name);
    // find sheet given state
    return stateSheetMap.at(state);
}

void NameStateSheetMap::readJSON(std::string filepath) {
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
    for (auto i = nameStrMap.begin(); i != nameStrMap.end(); i++) {
        // i returns key value pair
        std::string name = i->first;
        int sheet = 0;
        for (auto j = data[name].begin(); j != data[name].end(); j++) {
            // recur through each sheet data instance in json for this name
            // WARNING: This object, since it is created with [NEW], won't be deleted until explicitly done so! Be wary and ensure it is deleted down the line.
            SpriteSheet* newSheet = new SpriteSheet((std::string) data[name][sheet]["FilePathL"],
                                                    (std::string) data[name][sheet]["FilePathR"],
                                                    (int)         data[name][sheet]["TotalFrames"],
                                                    (float)       data[name][sheet]["Width"],
                                                    (float)       data[name][sheet]["Height"]);
            addSpriteSheet(nameStrMap[name],
                           stateStrMap[data[name][sheet]["State"]],
                           newSheet);
            sheet++;
        }
    }
}
