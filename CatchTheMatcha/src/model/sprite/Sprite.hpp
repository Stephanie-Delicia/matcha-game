#pragma once
#include <map>
#include <tuple>
#include <deque>
#include <iostream>
#include <SDL3/SDL.h>
#include "SpriteSheet.hpp"
#include "SpriteStruct.hpp"
#include "../../utils/Posn.hpp"
#include "../../utils/enums/NAME.h"
#include "../../utils/enums/STATE.h"
#include "../../utils/enums/DIRECTION.h"
#include "../../utils/sdl_utils/sdl_rect_utils.h"
#include "../../utils/data_maps/NameStateSheetMap.hpp"

// use a forward declaration here instead. A sprite state takes a sprite as input
class SpriteState;

/*
 A class representing a sprite (char, background texture, etc) in the game.
 Contains information such as name, location, and states such as direction the char is facing.
 */

class Sprite {
public:
    // constructors
    Sprite(NAME n) {
        name = n;
    };
    Sprite(NAME n, Posn p, DIRECTION d, STATE s) {
        name = n;
        posn = p;
        state = s;
        stateDir = d;
    };
    Sprite(NAME n, Posn p, DIRECTION d, STATE s, NameStateSheetMap* map) {
        name = n;
        posn = p;
        state = s;
        stateDir = d;
        sheetMap = map;
    };
    
    // getters
    float getAlpha() {return alpha;};
    float getAngle() { return angle; };
    NAME getName();
    Posn getPosn();
    STATE getState();
    float getFrameSpeed();
    SpriteStruct getData(); // get Sprite data in the form of a struct
    float getCurrFrameTime();
    DIRECTION getStateDir();
    SpriteSheet* getSheet(STATE s);
    NameStateSheetMap* getSheetMap();
    std::tuple<SDL_Rect, SDL_Rect> getSrcAndDest(); // get source and destination rectangles for blitzing
    SpriteState* getStateHandler() {return stateHandler;};
    
    // setters
    void setAlpha(float new_alpha) {alpha = new_alpha;};
    void setAngle(float degrees) { angle = degrees; };
    void setState(STATE newState);
    void setSheetMap(NameStateSheetMap* map);
    void setDir(DIRECTION newDir);
    void setPosn(float x, float y);
    void setFrameSpeed(float speed);
    void setCurrFrameTime(float time);
    void setStateHandler(SpriteState* state);
    
    // draw & updates
    void update();                            // update sprite based on curr state
    void resetSheet(STATE state);             // reset sheet frame
    void draw(SDL_Surface* windowSrfc);       // draws sprite on the given srfc
    void updateSheet(STATE state, int delta); // update sheet
    void handleInput(SDL_Event const &event); // update state of sprite given events
    
    // instead of using the singular STATE, we will have a queue to fulfill to handle more complex series of
    // keyboard inputs.
    void addState(STATE s);
    void removeState(STATE s);
    bool hasStateInQueue(STATE s);
    void clearQueue();
    
    // getters
    std::deque<STATE> getStates() { return statesToProcess; } ;

private:
    float angle = 0;       // in degrees
    float alpha = 1;       // 1 = fully opaque, 0 = fully transparent
    std::deque<STATE> statesToProcess;
    NAME name;                           // unique sprite name
    Posn posn;                           // (x,y). defaults to (0,0)
    STATE state = NONE;                  // whatever state sprite is in
    float frameSpeed = 2;                // rate of change in sprite posn
    DIRECTION stateDir = LEFT;           // direction that sprite faces
    NameStateSheetMap* sheetMap;         // map for accessing sheets
    float currFrameTime = -1.0;          // time for the current frame to continue be drawn, negative when you want to be stuck on the current frame
    SpriteState* stateHandler = nullptr; // sprite delegates to the state handler for updates, drawing, and handling events
};

