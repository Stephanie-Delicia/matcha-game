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
        {"start_screen_test", START_SCREEN_TEST},
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
        {"banner2_bkg", BANNER2_BKG},
        {"clear_blue_sky", CLEAR_BLUE_SKY},
        {"try_again_btn", TRY_AGAIN_BTN},
        {"next_lvl_btn", NEXT_LVL_BTN},
        {"resume_game_btn", RESUME_GAME_BTN},
        {"mini_instructions_box", MINI_INSTR_BOX},
        {"white_resume_btn", WHITE_RESUME_BTN},
        {"strawberry_matcha", STRAWBERRY_MATCHA},
        {"koicha", KOICHA},
        {"strawberry_mochi", STRAWBERRY_MOCHI},
        {"matcha_mochi", MATCHA_MOCHI},
        {"orange_sky", ORANGE_SKY},
        {"brick_ground", BRICK_GROUND}
    };
};
