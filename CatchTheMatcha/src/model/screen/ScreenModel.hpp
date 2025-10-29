/*
    A class that is a data container for what to draw on screen.
    The ScreenModel will have two queues of sprites to be drawn.
    The background queue will contain a predefined background to draw, then there is a main queue.
    The order of drawing is first the background queue, then the main queue.
    The main queue will have more interactive sprites.
 
    A ScreenModel will also have an update queue, that is, the sprites that will be updated when
    the game controller calls for updates.
 
    Before starting a game, a screen nav, containing a couple screen models, must be predefined.
 */
#pragma once
#include <deque>
#include <SDL3/SDL.h>
#include "../sprite/Sprite.hpp"
#include "../sprite/SpriteSheet.hpp"
#include "../../utils/enums/SCREEN.h"
#include "../../utils/data_maps/NameStateSheetMap.hpp"

class ScreenModel {
public:
    // constructors
    ScreenModel(){};
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
    bool isActive();
    SCREEN screenType();
    float getWidth() { return w; };
    float getHeight() { return h; };
    std::deque<Sprite*> getMainQ();
    std::deque<Sprite*> getUpdateQ();
    std::deque<Sprite*> getBackgroundQ();
    std::deque<Sprite*> getUiQ();
    
    // setters
    void setType(SCREEN t);
    void setWidth(int width);
    void setHeight(int height);
    
    // checks
    bool onScreen(Sprite* sprite);     // check if sprite is on main screen
    bool inBackground(Sprite* sprite); // check if sprite is in the background
    
    // change what gets drawn on this screen.
    void update();                                 // call for updating sprites in update queue in active screen
    void handleInput(SDL_Event const &event);      // handle inputs for sprites in update queue in active screen
    void handleWithoutMainSprite(SDL_Event const &event, Sprite* mainSprite);
    
    void activate();                               // activate screen
    void deactivate();                             // indicate screen is now inactive
    void emptyScreen();                            // empty the main queue, not background
    void addToMain(Sprite* sprite);                // add sprite to draw on screen
    void addToBG(Sprite* sprite);                  // add sprite to draw on screen
    void addToUpdate(Sprite* sprite);              // add sprite to update
    void removeMain(Sprite* sprite);               // remove a specific sprite if its on screen
    void removeBG(Sprite* sprite);                 // remove a specific sprite if its on screen
    void removeUpdate(Sprite* sprite);             // remove this sprite from getting updated
    void replaceMain(std::deque<Sprite*> m);       // just outright replace what queue gets drawn for main
    void replaceBackground(std::deque<Sprite*> q); // make changes to the background
    void replaceUpdate(std::deque<Sprite*> q);     // make changes to what sprites get updated
    void delayFrameTimes(float gameDelay, float timeElapsed);
    
    // UI queue
    void addToUI(Sprite* sprite);
    void removeUI(Sprite* sprite);
    void updateUI();
    void handleInputForUI(SDL_Event const &event);
    
    // create SDL surface from the queues
    SDL_Surface* returnMSurface();
    SDL_Surface* returnBGSurface();
    
private:
    float h;
    float w;                      // width and height
    bool active = false;          // is this the current screen the player is on?
    SCREEN screenT = TEST_SCREEN; // screen type enum
    
    // sprite queues
    std::deque<Sprite*> UiQueue;     // Ui elements to draw on screen like buttons
    std::deque<Sprite*> mQueue;      // sprites to draw on top of the background
    std::deque<Sprite*> bgQueue;     // background sprites to draw, like sky and ground
    std::deque<Sprite*> updateQueue; // sprites to draw on top of the background
    
    // creating a surface containing all sprites in the given queue
    SDL_Surface* createSurface(std::deque<Sprite*> spriteQueue);
};
