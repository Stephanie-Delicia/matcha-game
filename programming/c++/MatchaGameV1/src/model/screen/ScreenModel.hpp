#pragma once
#include <deque>
#include "SCREEN.h"
#include <SDL3/SDL.h>
#include "Sprite.hpp"

/*
 A class that represents a data container for what to draw on screen. The ScreenModel will have a queue of sprites to be drawn. The background queue will contain a predefined background to draw, then another main queue. The order of drawing will be first the background queue, then the main queue. The main queue will have more interactive methods. The background queue can be replaced.
 */

class ScreenModel {
public:
    // constructor
    ScreenModel();
    ScreenModel(int width, int height) {
        w = width;
        h = height;
    };
    ScreenModel(std::deque<Sprite*> q, int width, int height) {
        bgQueue = q;
    };
    ScreenModel(std::deque<Sprite*> q, std::deque<Sprite*> m, int width, int height) {
        bgQueue = q;
        mQueue = m;
        w = width;
        h = height;
    };
    
    // getters
    std::deque<Sprite*> getMainQ();
    std::deque<Sprite*> getBackgroundQ();
    // setters
    void setType(SCREEN t);
    void setWidth(int width);
    void setHeight(int height);
    
    // checks
    bool isActive();
    SCREEN screenType();
    bool onScreen(Sprite* sprite); // check if given sprite is in one of screen queues
    // change what gets drawn on this screen.
    void activate();                               // activate screen
    void deactivate();                             // indicate screen is now inactive
    void emptyScreen();                            // empty the main queue, except for the background
    void add(Sprite* sprite);                      // add sprite to draw on screen
    void remove(Sprite* sprite);                   // remove a specific sprite if its on screen
    void replace(std::deque<Sprite*> m);           // just outright replace what queue gets drawn
    void replaceBackground(std::deque<Sprite*> q); // make changes to the background
    
    // create SDL surface from the queues
    SDL_Surface returnMSurface();
    SDL_Surface returnBGSurface();
    
private:
    SCREEN screenT;              // what kind of screen is this?
    bool active = false;         // is this the current screen the player is on?
    std::deque<Sprite*> mQueue;  // sprites to draw on top of the background
    std::deque<Sprite*> bgQueue; // background sprites to draw, like sky and ground
    int h; // height
    int w; // width
    
    // creating a surface from queue
    SDL_Surface createSurface(std::deque<Sprite*> spriteQueue);
};
