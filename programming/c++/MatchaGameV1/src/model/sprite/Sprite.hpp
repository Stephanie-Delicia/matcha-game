#pragma once
#include <map>
#include <tuple>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteStruct.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game.
 Contains information such as name, location, and states such as direction the char is facing.
 */

class Sprite {
public:
    Sprite();
    Sprite(NAME n) {
        name = n;
    };
    Sprite(NAME n, Posn p, DIRECTION d, STATE s, NameStateSheetMap* map) {
        name = n;
        posn = p;
        state = s;
        stateDir = d;
        sheetMap = map;
    };
    
    // getters
    NAME getName();
    Posn getPosn();
    STATE getState();
    float getFrameSpeed();
    DIRECTION getStateDir();
    SpriteSheet* getSheet(STATE s);
    NameStateSheetMap* getSheetMap();
    
    // setters
    void setState(STATE newState);
    void setSheetMap(NameStateSheetMap* map);
    void setDir(DIRECTION newDir);
    void setPosn(float x, float y);
    void setFrameSpeed(float speed);
    
    // draw & updates
    void update();                            // update sprite based on curr state
    void resetSheet(STATE state);             // reset sheet frame
    void draw(SDL_Surface* windowSrfc);       // draws sprite on the given srfc
    void updateSheet(STATE state, int delta); // update sheet
    void handleInput(SDL_Event const &event); // update state of sprite given events
    
    SpriteStruct getData();                   // get Sprite data in the form of a struct
    // get source and destination rectangles for blitzing
    std::tuple<SDL_Rect, SDL_Rect> getSrcAndDest();

private:
    NAME name;                                     // unique sprite name
    Posn posn;                                     // (x,y). defaults to (0,0)
    STATE state = NONE;                            // whatever state sprite is in
    float frameSpeed = 1;                          // rate of change in sprite posn
    DIRECTION stateDir = LEFT;                     // direction that sprite faces
    NameStateSheetMap* sheetMap;                   // map for accessing sheets
};
