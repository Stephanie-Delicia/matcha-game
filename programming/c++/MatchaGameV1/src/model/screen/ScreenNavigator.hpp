#pragma once
#include <map>
#include <string>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SCREEN.h"
#include "ScreenModel.hpp"

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
    
    // checks
    bool isActive(ScreenModel* screen);
    bool containsScreen(ScreenModel* screen);
    
    // setters
    void setMainScreen(ScreenModel* screen);
    void addScreen(ScreenModel* screen);
    
    // load from JSON
    /*
     File should contain a list of lists. Each list contains the parameters per screen.
     */
    void loadJSON(std::string filepath);

 private:
    ScreenModel* mScreen = nullptr;           // screen displayed
    std::map<ScreenModel*, bool> screenMap;   // indicates if screen is active and stores screens
    std::map<std::string, Sprite*> spriteMap;
    std::map<std::string, SCREEN> screenTypeMap = { { "Gameplay", GAMEPLAY_SCREEN } };
};
