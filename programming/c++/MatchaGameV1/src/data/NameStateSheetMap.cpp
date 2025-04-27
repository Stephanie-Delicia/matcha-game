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

NameStateSheetMap::~NameStateSheetMap() {
    // TODO
}

// TODO: catch error if value does not exist
SpriteSheet* NameStateSheetMap::getSpriteSheet(NAME name, STATE state) {
    // find name
    std::map<STATE, SpriteSheet*> stateSheetMap = nameStateSheetMap.at(name);
    // find sheet given state
    return stateSheetMap.at(state);
}

void NameStateSheetMap::readJSON(std::string filepath) {
    // TODO: to recur through map once I have all the textures made for other chars.
    // TODO: read in json file to add data
    std::ifstream file(filepath);
    
    // std::cout << std::filesystem::exists(filepath) << "\n";
    
    // TODO: Catch error
    if (!file.is_open()) {
            std::cerr << "Error opening file" << std::endl;
        }
    
    nlohmann::json data;
    file >> data;
    file.close();
    
//    std::cout << data["Winnie"]["FilePathL"] << "\n";
//    std::cout << data["Winnie"]["FilePathR"] << "\n";
//    std::cout << data["Winnie"]["TotalFrames"] << "\n";
//    std::cout << data["Winnie"]["Width"] << "\n";
//    std::cout << data["Winnie"]["Height"] << "\n";
    
    // WARNING: This object, since it is created with [NEW], won't be deleted until explicitly done so! Be wary and ensure it is deleted down the line.
    SpriteSheet* sheet = new SpriteSheet((std::string) data["Winnie"]["FilePathL"],
                                    (std::string) data["Winnie"]["FilePathR"],
                                    (int)         data["Winnie"]["TotalFrames"],
                                    (float)       data["Winnie"]["Width"],
                                    (float)       data["Winnie"]["Height"]);
    addSpriteSheet(nameStrMap[data["Winnie"]["Name"]],
                   stateStrMap[data["Winnie"]["State"]],
                   sheet);
}
