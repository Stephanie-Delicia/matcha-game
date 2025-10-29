#pragma once
#include <map>
#include <string>
#include <SDL3/SDL.h>
#include "ScreenModel.hpp"
#include "../sprite/Sprite.hpp"
#include "../sprite/SpriteSheet.hpp"
#include "../../utils/enums/SCREEN.h"
#include "../../utils/data_maps/NameSpriteMap.hpp"
#include "../../utils/data_maps/NameStateSheetMap.hpp"

/*
 A class that contains all screens for a game model. Only one screen can be active at a time!
 */

class ScreenNavigator {
public:
    // constructor
    ScreenNavigator(){};
    ScreenNavigator(ScreenModel* mainScreen);
    ScreenNavigator(std::map<ScreenModel*, bool> screens);
    ScreenNavigator(std::map<ScreenModel*, bool> screens, ScreenModel* mainScreen);
   
    // getter
    ScreenModel* getMainScreen();
    std::map<ScreenModel*, bool> getScreens();
    ScreenModel* getScreen(SCREEN type); // get screen given type. If not found, return nullptr
    
    // checks
    bool isActive(ScreenModel* screen);
    bool containsScreen(ScreenModel* screen);
    
    // setters
    void setMainScreen(ScreenModel* screen);
    void setStartScreen(ScreenModel* screen) { startScreen = screen; } ;
    void addScreen(ScreenModel* screen);
    void setNameSpriteMap(NameSpriteMap* map) { nameSpriteMap = map; };
    
    /*
     File should contain a list of lists. Each list contains the parameters per screen.
     */
    void loadJSON(std::string filepath);

 private:
    ScreenModel* mScreen = nullptr;           // screen displayed
    ScreenModel* startScreen = nullptr;
    NameSpriteMap* nameSpriteMap;             // NAME to Sprite* map
    std::map<ScreenModel*, bool> screenMap;   // indicates if screen is active and stores screens
    std::map<std::string, NAME> strNameMap = {  {"winnie",            WINNIE},
                                                {"pleasant_sky",      PLEASANT_SKY},
                                                {"start_screen_test", START_SCREEN_TEST},
                                                {"start_button_test", START_BUTTON_TEST},
                                                {"replay_button",     REPLAY_BUTTON},
                                                {"black_screen",      BLACK_SCREEN},
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
    
    std::map<std::string, SCREEN> screenTypeMap = { {"start",    START_SCREEN},
                                                    {"gameplay", GAMEPLAY_SCREEN} };
};
