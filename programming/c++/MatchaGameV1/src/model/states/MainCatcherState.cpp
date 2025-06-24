#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
#include "MainSprite.hpp"
#include "MainCatcherState.hpp"
#include "sdl_rect_utils.h"
/*
 A class representing the command for handling the walking state for a sprite.
 Rather than by input.type, use the key states for switch statements instead.
 Reason being that even if I hold one key down, if I WAS holding multiple keys down, but ONE OF THEM is lifted,
 this will automatically return a KEY_UP event. Checking the key array is more accurate and will correctly show which
 keys are still pressed down.
 */
void MainCatcherState::handleInput(Sprite* sprite, const SDL_Event &input) {
    const bool *keys = SDL_GetKeyboardState(nullptr);
    bool isUpPressed    = keys[SDL_SCANCODE_UP];
    bool isDownPressed  = keys[SDL_SCANCODE_DOWN];
    bool isLeftPressed  = keys[SDL_SCANCODE_LEFT];
    bool isRightPressed = keys[SDL_SCANCODE_RIGHT];
    bool isSpacePressed = keys[SDL_SCANCODE_SPACE];
    bool keyDown = (isUpPressed || isDownPressed || isLeftPressed || isRightPressed || isSpacePressed); // are any of these pressed down?
    if (keyDown) {
        if (isLeftPressed && isRightPressed)
        {
            sprite->addState(WALKING);
        }
        else if (isLeftPressed)
        {
            sprite->addState(WALKING);
            sprite->setDir(DIRECTION::LEFT);
        }
        else if (isRightPressed)
        {
            sprite->addState(WALKING);
            sprite->setDir(DIRECTION::RIGHT);
        }
        else if (isUpPressed)
        {
            if (!sprite->hasStateInQueue(JUMPING)) {
                sprite->addState(IDLE);
                sprite->setDir(sprite->getStateDir());
            }
        }
        else if (isDownPressed)
        {
            if (!sprite->hasStateInQueue(JUMPING)) {
                sprite->addState(IDLE);
                sprite->setDir(sprite->getStateDir());
            }
        }
    } else { // NO KEY PRESSED
        if (!sprite->hasStateInQueue(JUMPING) or sprite->getStates().size() == 0) {
            idleC.update(sprite); // reset frame of state before idle state
            sprite->addState(IDLE);
        }
    }
        
     if (isSpacePressed) {
         if (!sprite->hasStateInQueue(JUMPING)) {
             setJumpingCommand();
             sprite->addState(JUMPING);
         }
    }
}

void MainCatcherState::update(Sprite* sprite) {
    std::deque<STATE> stateQueue = sprite->getStates();
    std::deque<STATE> statesToRemove;
    for (STATE s : stateQueue) {
        // delegates to command
        STATE currState = s;
        sprite->setState(s);
        switch (currState) {
            case IDLE: {
                idleC.update(sprite);
                statesToRemove.push_back(IDLE);
                break;
            }
            case WALKING: {
                walkingC.update(sprite);
                statesToRemove.push_back(WALKING);
                break;
            }
            case BLINKING: {
                break;
            }
            case RUNNING: {
                break;
            }
            case DRINKING: {
                break;
            }
            case TRANSLATE: {
                break;
            }
            case PRESSED: {
                break;
            }
            case HOVER: {
                break;
            }
            case JUMPING: {
                // NOTE: the jumping state removes itself!
                jumpingC.update(sprite);
                if (jumpingC.getIsDone()) {
                    statesToRemove.push_back(JUMPING);
                    jumpingC.setDone(false);
                }
                break;
            }
            case NONE: {
                break;
            }
        }
    }
    
    // remove state afterwards
    for (STATE s : statesToRemove) {
        sprite->removeState(s);
    }
}

void MainCatcherState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    bool success = 0;
    // acquire sprite data
    std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
    SpriteStruct spriteData = sprite->getData();
    SpriteSheet* sheet = spriteData.sheet;
    SDL_Rect frameRect = std::get<0>(rects);
    SDL_Rect destRect = std::get<1>(rects);
    
    // draw based on direction
    switch (spriteData.dir) {
        case LEFT: {
            success = SDL_BlitSurface(sheet->getSrfcL(), &frameRect, windowSrfc, &destRect);
            if (success < 1) {
                fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
            }
            break;
        }
        case RIGHT: {
            success = SDL_BlitSurface(sheet->getSrfcR(), &frameRect, windowSrfc, &destRect);
            if (success < 1) {
                fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
            }
            break;
        }
        case UP: {
            break;
        }
        case DOWN: {
            break;
        }
    }
}
