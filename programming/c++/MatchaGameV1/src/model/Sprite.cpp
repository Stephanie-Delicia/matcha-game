#include "Sprite.hpp"
#include <map>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteSheet.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game. Contains information such as name, location, and states such as direction the char is facing.
 */

Sprite::~Sprite() {
}

NAME Sprite::getName() {
    return name;
}

DIRECTION Sprite::getStateDir() {
    return stateDir;
}

STATE Sprite::getState() {
    return state;
}

Posn Sprite::getPosn() {
    return posn;
}

float Sprite::getFrameSpeed() {
    return frameSpeed;
}

SpriteSheet* Sprite::getSheet(STATE s) {
    return sheetMap->getSpriteSheet(name, s);
}

void Sprite::setDir(DIRECTION newDir) {
    stateDir = newDir;
}

void Sprite::setFrameSpeed(float speed) {
    frameSpeed = speed;
}

void Sprite::setState(STATE newState) {
    state = newState;
}

void Sprite::setPosn(float x, float y) {
    posn.setX(x);
    posn.setY(y);
}

void Sprite::updateSheet(SpriteSheet sheet, int newFrameNum) {
    sheet.setFrameNum(newFrameNum);
}

void Sprite::handleInput(SDL_Event const &event) {
    switch (event.type)
    {
        case SDL_EVENT_KEY_DOWN: {
            const bool *keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_UP] == 1)
            {
                setState(STATE::IDLE);
                setDir(DIRECTION::UP);
            }
            else if (keys[SDL_SCANCODE_DOWN] == 1)
            {
                setState(STATE::IDLE);
                setDir(DIRECTION::DOWN);
            }
            else if (keys[SDL_SCANCODE_LEFT] == 1)
            {
                setState(STATE::WALKING);
                setDir(DIRECTION::LEFT);
            }
            else if (keys[SDL_SCANCODE_RIGHT] == 1)
            {
                setState(STATE::WALKING);
                setDir(DIRECTION::RIGHT);
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            // reset last state sheet
            // updateSheet(getSheet(state), 0); // reset to first frame
            setState(STATE::IDLE);
            break;
        }
    }
}

void Sprite::update() {
    switch (state)
    {
        case STATE::IDLE : {
            break;
        }
            
        case STATE::WALKING : {
            switch (stateDir)
            {
                case DIRECTION::LEFT: {
                    // give command the name, state, and framerate
                    // updateSheet(getSheet(state), getSheet(state).getCurrFr() + 1);
                    setPosn(posn.getX() - frameSpeed, posn.getY());
                }
                    
                case DIRECTION::RIGHT: {
                    // updateSheet(getSheet(state), getSheet(state).getCurrFr() + 1);
                    setPosn(posn.getX() + frameSpeed, posn.getY());
                }
                case UP: {
                    
                    break;
                }
                case DOWN: {
                    
                    break;
                }
            }
            break;
        }
            
        case STATE::RUNNING: {
            break;
        }
            
        case STATE::NONE: {
            // NONE
            break;
        }
            
        case STATE::BLINKING: {
            // NONE
            break;
        }
            
        case STATE::DRINKING: {
            // NONE
            break;
        }
    }
}

void Sprite::drawSprite(SDL_Surface *windowSrfc) {
    // TODO
}
