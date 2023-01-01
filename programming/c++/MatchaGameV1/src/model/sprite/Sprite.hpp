#pragma once
#include <map>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game. Contains information such as name, location, and states such as direction the char is facing.
 */

class Sprite {
public:
    Sprite(NAME n, Posn p, DIRECTION d, STATE s, NameStateSheetMap* map) {
        name = n;
        posn = p;
        state = s;
        stateDir = d;
        sheetMap = map;
    };
    ~Sprite();
    
    // getters
    NAME getName();
    Posn getPosn();
    STATE getState();
    float getFrameSpeed();
    DIRECTION getStateDir();
    SpriteSheet* getSheet(STATE s);
    
    // setters
    void setFrameSpeed(float speed);
    void setPosn(float x, float y);
    void setState(STATE newState);
    void setDir(DIRECTION newDir);
    
    // draw & updates
    void update();                            // update sprite based on curr state
    void resetSheet(STATE state);             // reset sheet frame
    void updateSheet(STATE state, int delta); // update sheet
    void handleInput(SDL_Event const &event); // update state of sprite given events
    void drawSprite(SDL_Surface* windowSrfc); // draws sprite on the given srfc

private:
    NAME name;                                     // unique sprite name
    Posn posn;                                     // (x,y). defaults to (0,0)
    float frameSpeed = 1;                          // rate of change in sprite posn
    STATE state;                                   // whatever state sprite is in
    DIRECTION stateDir;                            // direction sprite faces
    NameStateSheetMap* sheetMap;                   // map for accessing sheets
};
