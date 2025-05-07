#pragma once
#include <map>
#include <queue>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"
/*
 A base class that represents the game model, carrier of all game data.
 This class contains:
 - Width and height for display window.
 - Game name
 - The main sprite that the player controls.
 - Data for obtaining sprite sheets and screens.
 - The controller contains a model and updates model parameters.
 */

class GameModel {
public:
    // constructors
    GameModel();
    GameModel(float w, float h, std::string name);
    GameModel(float w, float h, std::string name, Sprite* mainSprite, NameStateSheetMap* map, ScreenNavigator* nav);
    // getters
    float              getWidth();
    float              getHeight();
    std::string        getGameName();
    Sprite*            getMainPlayer();
    ScreenModel*       getActiveScreen();
    ScreenNavigator*   getNavigator();
    NameStateSheetMap* getNameToSheetMap();
    
    // setters
    void setWidth(float w);
    void setHeight(float h);
    void setGameName(std::string name);
    void setMainPlayer(Sprite* sprite);
    void setScreenNav(ScreenNavigator* nav);
    void setActiveScreen(ScreenModel* screen);
    void setNameToSheetMap(NameStateSheetMap* map);
    void setNameToSpriteMap(NameSpriteMap* map);
    
    // for the controller
    
private:
    // params
    Sprite*            mPlayer;           // main sprite to control on screen
    std::string        gameName;          // game name
    ScreenNavigator*   screenNav;         // all screens. can use to see which screen is active.
    float              screenWidth;       // window's width
    float              screenHeight;      // window's height
    NameSpriteMap*     nameSpriteMap;
    NameStateSheetMap* nameStateSheetMap; // mapping to Spritesheets given NAME and STATE
};
