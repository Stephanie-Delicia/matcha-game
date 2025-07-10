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
            {"start_button_test", START_BUTTON_TEST},
            {"replay_button", REPLAY_BUTTON},
            {"black_screen", BLACK_SCREEN},
            {"menu_box", MENU_BOX},
            {"menu_button", MENU_BUTTON},
            {"return_button", RETURN_BUTTON},
            {"back_to_start_scrn_btn", BACK_TO_START_SCRN_BTN},
            {"exit_button", EXIT_BUTTON},
            {"instructions_btn", INSTRUCTIONS_BTN},
            {"instructions_box", INSTRUCTIONS_BOX},
            {"beta_matcha", BETA_MATCHA},
            {"how_to_play_start_btn", HOW_TO_PLAY_START_BTN},
            {"small_exit_btn", SMALL_EXIT_BUTTON},
            {"resume_btn", RESUME_BUTTON},
            {"beta_title_card", BETA_TITLE_CARD},
            {"winnie_drinking", WINNIE_DRINKING},
            {"start_banner1", START_BANNER1},
            {"start_banner2", START_BANNER2},
            {"banner1_bkg", BANNER1_BKG},
            {"banner2_bkg", BANNER2_BKG}
        };
        stateStrMap = {
            {"walking", WALKING},
            {"jumping", JUMPING},
            {"idle", IDLE},
            {"translate", TRANSLATE},
            {"pressed", PRESSED},
            {"hover", HOVER},
            {"none", NONE},
            {"scrolling_banner", SCROLLING_BANNER},
            {"diagonal_scrolling", DIAGONAL_BANNER}
        };
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
