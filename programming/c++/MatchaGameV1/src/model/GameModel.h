#pragma once
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"
/*
 An abstract class that represents the game model, carrier of all game data.
 This class contains:
 - Width and height for display window.
 - Game name
 - The main sprite that the player controls.
 - Data for obtaining sprite sheets and screens.
 */

class GameModel {
public:
    // constructors
    GameModel();
    GameModel(float width, float height, std::string gameName);
    GameModel(float width, float height, std::string gameName, Sprite* mPlayer, NameStateSheetMap sheetMap, ScreenNavigator screenNav);
    // getters
    float             getWidth();
    float             getHeight();
    std::string       getGameName();
    Sprite*           getMainPlayer();
    ScreenModel*      getActiveScreen();
    ScreenNavigator   getNavigator();
    NameStateSheetMap getNameToSheetMap();
    
    // setters
    void setWidth(float width);
    void setHeight(float height);
    void setGameName(std::string name);
    void setMainPlayer(Sprite* sprite);
    void setScreenNav(ScreenNavigator* nav);
    void setActiveScreen(ScreenModel* screen);
    void setNameToSheetMap(NameStateSheetMap map);
    
    // updating methods for the controller to use
    void updateSprite(Sprite* sprite);
    void updateScreen(ScreenModel* sm);
    
private:
    // params
    Sprite* mPlayer;                     // main sprite to control on screen
    float screenWidth;                   // window's width
    float screenHeight;                  // window's height
    std::string gameName;                // game name
    ScreenNavigator screenNav;           // all screens. see which screen is active.
    NameStateSheetMap nameStateSheetMap; // mapping to Spritesheets given NAME and STATE
};
