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

/*
 A class that represents a data container for what to draw on screen. The ScreenModel will have a queue of sprites to be drawn. The background queue will contain a predefined background to draw, then another main queue. The order of drawing will be first the background queue, then the main queue. The main queue will have more interactive methods. The background queue can be replaced.
 */

class ScreenModel {
public:
    // constructor
    ScreenModel();
    ScreenModel(std::queue<Sprite*> q) {
        bgQueue = q;
    };
    ScreenModel(std::queue<Sprite*> q, std::queue<Sprite*> m) {
        bgQueue = q;
        mQueue = m;
    };
    
    // getters
    std::queue<Sprite*> getMainQ();
    std::queue<Sprite*> getBackgroundQ();
    
    // checks
    bool isActive();
    bool onScreen(Sprite* sprite); // check if given sprite is in one of screen queues
    SCREEN screenType();
    
    // change what gets drawn on this screen.
    void emptyScreen();                            // empty the main queue, except for the background
    void add(Sprite* sprite);                      // add sprite to draw on screen
    void remove(Sprite* sprite);                   // remove a specific sprite if its on screen
    void replace(std::queue<Sprite*> m);           // just outright replace what queue gets drawn
    void replaceBackground(std::queue<Sprite*> q); // make changes to the background
    
private:
    std::queue<Sprite*> mQueue;  // sprites to draw on top of the background
    std::queue<Sprite*> bgQueue; // background sprites to draw, like sky and ground
    bool active = false;         // is this the current screen the player is on?
    SCREEN type;                 // what kind of screen is this?
};
