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
        stateDir = d;
        state = s;
        sheetMap = map;
    };
    ~Sprite();
    
    // getters
    NAME getName();
    Posn getPosn();
    STATE getState();
    DIRECTION getStateDir();
    float getFrameSpeed();
    SpriteSheet* getSheet(STATE s); // helper to grab sheet given state and direction
    
    // setters
    void setFrameSpeed(float speed);
    void setPosn(float x, float y);
    void setState(STATE newState);
    void setDir(DIRECTION newDir);
    
    // draw & updates
    void updateSheet(SpriteSheet sheet, int newFrameNum); // update sheet
    void handleInput(SDL_Event const &event); // update state of sprite given events
    void update();                            // update sprite based on curr state
    void drawSprite(SDL_Surface* windowSrfc); // draws sprite on the given srfc

private:
    NAME name;                                     // unique sprite name
    Posn posn;                                     // (x,y). defaults to (0,0)
    DIRECTION stateDir;                            // direction sprite faces
    STATE state;                                   // whatever state sprite is in
    NameStateSheetMap* sheetMap;                    // map for accessing sheets
    float frameSpeed = 1;                          // default = 1
};
