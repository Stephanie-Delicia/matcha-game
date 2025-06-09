#pragma once
#include <stdio.h>
#include "NAME.h"
#include "STATE.h"
#include "DIRECTION.h"
#include "SpriteSheet.hpp"
#include <map>
#include <string>

// A nested mapping data structure that refers to Name, then state, then finally Map.
// For JSON reading, the JSON format should be in the form:
/*
 "Name_1": [
    {sheet_1 parameters},
    ...,
    {sheet_n parameters}
 ],
 
 "Name_2": [
    ...
 ]
 
 .
 .
 .
 
 */

class NameStateSheetMap {
public:
    // constructor/destructor
    NameStateSheetMap() {
        nameStrMap = {
            {"winnie", WINNIE},
            {"pleasant_sky", PLEASANT_SKY},
            {"test_box", TEST_BOX},
            {"start_screen_test", START_SCREEN_TEST},
            {"start_button_test", START_BUTTON_TEST}};
        stateStrMap = {
            {"walking", WALKING},
            {"idle", IDLE},
            {"translate", TRANSLATE},
            {"pressed", PRESSED},
            {"hover", HOVER}};
    };
    
    // utils
    SpriteSheet* getSpriteSheet(NAME name, STATE state);             // returns sprite sheet
    void addSpriteSheet(NAME name, STATE state, SpriteSheet* sheet); // add a sprite sheet
    void readJSON(std::string filepath);                             // add sprite sheets according to json file
    
private:
    std::map<NAME, std::map<STATE, SpriteSheet*>> nameStateSheetMap;
    std::map<std::string, NAME> nameStrMap;
    std::map<std::string, STATE> stateStrMap;
};
