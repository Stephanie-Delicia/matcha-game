#pragma once
#include <map>
#include <string>
#include <queue>
#include <iostream>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SCREEN.h"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "ScreenModel.hpp"

/*
 A class that contains all screens for a game model.
 Only one screen can be active at a time!
 */

class ScreenNavigator {
public:
    // constructor
    ScreenNavigator();
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

 private:
    // Map of screens. Screen : bool, where bool indicates if screen is active.
    std::map<ScreenModel*, bool> screenMap;
    ScreenModel* mScreen; // screen being displayed
};
