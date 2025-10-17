#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
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
    bool isAKeyPressed  = keys[SDL_SCANCODE_A];
    bool keyDown = (isUpPressed ||
                    isDownPressed ||
                    isLeftPressed ||
                    isRightPressed ||
                    isSpacePressed ||
                    isAKeyPressed);
    
    if (!isTimerSetUp) {
        setJumpingCommand();
    }
    
    if (isAKeyPressed and (isRightPressed or isLeftPressed)) {
        sprite->addState(RUNNING);
        // ensure walking isnt already in queue
        if (sprite->hasStateInQueue(WALKING)) {
            sprite->removeState(WALKING);
        }
    } else if (isAKeyPressed) {
        sprite->addState(IDLE);
        if (sprite->hasStateInQueue(RUNNING)) {
            sprite->removeState(RUNNING);
        }
    }
    
    if (keyDown) {
        if (isLeftPressed && isRightPressed)
        {
            if (!sprite->hasStateInQueue(RUNNING)) {
                sprite->addState(WALKING);
            }
        }
        else if (isLeftPressed)
        {
            if (!sprite->hasStateInQueue(RUNNING)) {
                sprite->addState(WALKING);
            }
            sprite->setDir(DIRECTION::LEFT);
        }
        else if (isRightPressed)
        {
            if (!sprite->hasStateInQueue(RUNNING)) {
                sprite->addState(WALKING);
            }
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
    } else {
        // NO KEY PRESSED
        if (!sprite->hasStateInQueue(JUMPING) or sprite->getStates().size() == 0) {
            idleC.update(sprite); // reset frame of state before idle state
            sprite->addState(IDLE);
        }
    }
        
     if (isSpacePressed) {
         if (!sprite->hasStateInQueue(JUMPING)) {
             sprite->addState(JUMPING);
         }
    }
}

void MainCatcherState::update(Sprite* sprite) {
    std::deque<STATE> stateQueue = sprite->getStates();
    std::deque<STATE> statesToRemove;
    auto find_iterator = std::find(stateQueue.begin(), stateQueue.end(), JUMPING);
    bool is_jumping = (find_iterator != stateQueue.end());
    auto find_iterator2 = std::find(stateQueue.begin(), stateQueue.end(), VICTORY_POSE);
    bool is_vic_pose = (find_iterator2 != stateQueue.end());
    auto find_iterator3 = std::find(stateQueue.begin(), stateQueue.end(), LOSE_POSE);
    bool is_lose_pose = (find_iterator3 != stateQueue.end());
    auto find_iterator4 = std::find(stateQueue.begin(), stateQueue.end(), SPEED_BOOST);
    bool has_speed_boost = (find_iterator4 != stateQueue.end());
    if (!has_speed_boost and speedBoostC.getImages().size() > 0) {
        speedBoostC.getImages().clear();
        speedBoostC.setStateDone(false);
        speedBoostC.setIsSpeedBoosted(false);
    }
    for (STATE s : stateQueue) {
        // delegates to command
        STATE currState = s;
        if (is_jumping) {
            sprite->setState(JUMPING);
        } else if (is_vic_pose) {
            sprite->setState(VICTORY_POSE);
        } else if (is_lose_pose) {
            sprite->setState(LOSE_POSE);
        } else {
            loseC.setShiftDone(false); // this should probably be moved to when the state is being removed
            sprite->setState(s);
        }
        //std::cout << "speedBoostC.getIsDone(): " << speedBoostC.getIsDone() << ". [MainCatcherState, update()]\n";
        if (has_speed_boost and currState != SPEED_BOOST and !speedBoostC.getIsDone()) {
            speedBoostC.update(sprite);
            speedBoostC.addTuple(sprite); // add tuple before the sprite gets updated
        }
        switch (currState) {
            case SPEED_BOOST: {
//                std::cout << "SPEED_BOOST UPDATE. [MainCharState]\n";
                 // updates the image tuples info
                if (speedBoostC.getIsDone()) {
//                    std::cout << "Speed boost done. [MainCharState]\n";
                    statesToRemove.push_back(SPEED_BOOST);
                    speedBoostC.resetSpeedBoostCommand(sprite);
                }
                break;
            }
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
                runningC.update(sprite);
                statesToRemove.push_back(RUNNING);
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
            case LOSE_POSE: {
                if (!sprite->hasStateInQueue(JUMPING)) {
                    sprite->setState(LOSE_POSE);
                }
                loseC.update(sprite);
                // We don't do anything else here, just let the pose animation play itself out
                break;
            }
            case VICTORY_POSE: {
                if (!sprite->hasStateInQueue(JUMPING)) {
                    sprite->setState(VICTORY_POSE);
                }
                victoryC.update(sprite);
                // We don't do anything else here, just let the pose animation play itself out
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
            default: {
                break;
            }
        }
    }
    
    // remove state afterwards
    for (STATE s : statesToRemove) {
        if (s == SPEED_BOOST) {
            speedBoostC.setStateDone(false);
        }
        sprite->removeState(s);
    }
}

void MainCatcherState::drawBoostImages(Sprite* sprite, SDL_Surface* windowSrfc) {
    if (speedBoostC.getImages().size() > 0) {
        // obtain the deque of tuples which are in the command.
        std::deque<std::tuple<Posn, STATE, DIRECTION>> images = speedBoostC.getImages();
        // From the front to the back: We find the incrementor for alpha, then we simple draw each once according to
        // their info in the tuple.
        
        // for alpha, let's start off at the halfway point of 255 (max) and divide by the size of images
        float alphaIncrementor = (255 / 4)/images.size();
        float currAlpha;
        int counter = 1;
//        std::cout << "size images: " << images.size() << ". [MainCatcherState, drawBoostImages()]\n";
        
        for (auto imgTuple = images.rbegin(); imgTuple != images.rend(); ++imgTuple) {
            // get the spritesheet for THIS tuple's state
            DIRECTION tupleDir = std::get<2>(*imgTuple);
            STATE tupleState = std::get<1>(*imgTuple);
            Posn tuplePosn = std::get<0>(*imgTuple);
            SpriteSheet* sheet = sprite->getSheet(tupleState);
            SDL_Rect frameRect = roundRect(sheet->getFrameRect());
            SDL_Rect destRect = {tuplePosn.getIntX(), tuplePosn.getIntY(), frameRect.w, frameRect.h};
//            std::cout << "tuple x posn: " << tuplePosn.getX() << ". [MainCatcherState, drawBoostImages()]\n";
//            std::cout << "tuple y posn: " << tuplePosn.getY() << ". [MainCatcherState, drawBoostImages()]\n";
            
            // set alpha and blitz
            currAlpha = counter * alphaIncrementor;
            counter++;
            switch (tupleDir) {
                case LEFT: {
                    SDL_SetSurfaceAlphaMod(sheet->getSrfcL(), currAlpha);
                    bool success = SDL_BlitSurface(sheet->getSrfcL(), &frameRect, windowSrfc, &destRect);
                    SDL_SetSurfaceAlphaMod(sheet->getSrfcL(), 255);
                    break;
                }
                case RIGHT: {
                    SDL_SetSurfaceAlphaMod(sheet->getSrfcR(), currAlpha);
                    bool success = SDL_BlitSurface(sheet->getSrfcR(), &frameRect, windowSrfc, &destRect);
                    SDL_SetSurfaceAlphaMod(sheet->getSrfcR(), 255);
                    break;
                }
                default: {
                    break;
                }
            }
        }
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
    
    std::deque<STATE> stateQueue = sprite->getStates();
    auto find_iterator4 = std::find(stateQueue.begin(), stateQueue.end(), SPEED_BOOST);
    bool has_speed_boost = (find_iterator4 != stateQueue.end());
    
    // if the sprite has a speed boost, draw the speed boost images if there are any here
    if (has_speed_boost) {
        drawBoostImages(sprite, windowSrfc);
    }
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

void  MainCatcherState::resetCommands(Sprite* sprite) {
    // TODO: the setStateDone should hold True untill all instances of SPEED BOOST STATES are removed from queue
    speedBoostC.getImages().clear();
    speedBoostC.resetLastImageTime();
    // speedBoostC.setStateDone(false);
    speedBoostC.setIsSpeedBoosted(false);
    sprite->setFrameSpeed(sprite->getFrameSpeed() - speedBoostC.getSpeedBoost());
};
