/*
 A base class that represents the game model, carrier of all game data.
 This class contains:
 - Width and height for display window.
 - Game name
 - The main sprite that the player controls.
 - Data objects for obtaining sprite sheets or game screens.
 - The controller contains a model and updates model parameters.
 */
#pragma once
#include <map>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"

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
    NameSpriteMap*     getNameSpriteMap();
    
    // setters

    void setWidth(float w);
    void setHeight(float h);
    void setGameName(std::string name);
    void setMainPlayer(Sprite* sprite);
    void setScreenNav(ScreenNavigator* nav);
    void setActiveScreen(ScreenModel* screen);
    void setNameToSheetMap(NameStateSheetMap* map);
    void setNameToSpriteMap(NameSpriteMap* map);
    
    // for the controller to use
    virtual void update();                                  // calls on an transformation updates for the active screen
    void handleInput(const SDL_Event &event);                  // calls on state updates for the active screen
    void handleWithoutMainSprite(const SDL_Event &event);      // calls on state updates for the active screen
    void handleMainSprite(const SDL_Event &event);             // calls on state updates for the active screen
    void delayFrameTimes(float gameDelay, float timeElapsed);  // calls on active screen to delay sprite frame times accordingly
    void updateUI();
    void handleInputForUI(const SDL_Event &event);
    
 protected: // derived classes have access to these fields/methods
    // params
    Sprite*            mPlayer;           // main sprite to control on screen
    std::string        gameName;          // game name
    ScreenNavigator*   screenNav;         // all screens. can use to see which screen is active.
    float              screenWidth;       // window's width
    float              screenHeight;      // window's height
    NameSpriteMap*     nameSpriteMap;     // mapping to sprite given NAME
    NameStateSheetMap* nameStateSheetMap; // mapping to Spritesheets given NAME and STATE
};
