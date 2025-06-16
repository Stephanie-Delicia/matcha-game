#pragma once
#include <map>
#include <string>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SCREEN.h"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"

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
    std::map<std::string, NAME> strNameMap = { {"winnie",            WINNIE},
                                               {"pleasant_sky",      PLEASANT_SKY},
                                               {"start_screen_test", START_SCREEN_TEST},
                                               {"start_button_test", START_BUTTON_TEST},
                                               {"replay_button",     REPLAY_BUTTON},
                                               {"black_screen", BLACK_SCREEN} };
    
    std::map<std::string, SCREEN> screenTypeMap = { {"start",    START_SCREEN},
                                                    {"gameplay", GAMEPLAY_SCREEN} };
};
