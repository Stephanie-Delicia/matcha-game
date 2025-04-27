// A nested mapping data structure that refers to Name, then state, then finally Map.
#pragma once
#include <stdio.h>
#include "NAME.h"
#include "STATE.h"
#include "DIRECTION.h"
#include "SpriteSheet.hpp"
#include <map>
#include <string>

class NameStateSheetMap {
public:
    // constructor/destructor
    NameStateSheetMap() {
        nameStrMap = {
            {"Winnie", WINNIE},
            {"Pearl", PEARL},
            {"Soma", SOMA},
            {"Ifesola", IFESOLA}};
        stateStrMap = {
            {"Walking", WALKING},
            {"Idle", IDLE}};
    };
    ~NameStateSheetMap();
    
    // utils
    SpriteSheet* getSpriteSheet(NAME name, STATE state);              // returns sprite sheet
    void addSpriteSheet(NAME name, STATE state, SpriteSheet* sheet); // add a sprite sheet
    void readJSON(std::string filepath);                             // add sprite sheets according to json file
    
private:
    std::map<NAME, std::map<STATE, SpriteSheet*>> nameStateSheetMap;
    std::map<std::string, NAME> nameStrMap;
    std::map<std::string, STATE> stateStrMap;
};
