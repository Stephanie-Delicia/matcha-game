/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "VictoryCommand.hpp"
#include "Posn.hpp"
#include <iostream>
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "Sprite.hpp"

void VictoryCommand::update(Sprite* sprite) {
    if (startTime == 0) {
        startTime = timer->getTicks();
    }
    
    DIRECTION stateDir = sprite->getStateDir();
    Posn posn = sprite->getPosn();
    float currFrameTime = sprite->getCurrFrameTime();
    float x = posn.getX();
    float y = posn.getY();
    
    // get sheet width
    SpriteSheet* sheet = sprite->getSheet(sprite->getState());
    
    timeElapsed = (timer->getTicks() - startTime); // ms
    
    float totalTime = animDuration;
    float timePerFrame = (totalTime / sheet->getTotalFr());
    float thisFrameTime = ((sheet->getCurrFr() + 1) * timePerFrame);
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            // if (timeElapsed >= thisFrameTime) {
            if (currFrameTime <= 0.0) {
                if (sprite->getSheet(VICTORY_POSE)->getCurrFr() ==
                    sprite->getSheet(VICTORY_POSE)->getTotalFr() - 1) {
                    // no reset, we want to stay on the last frame basically
                } else {
                    sprite->updateSheet(VICTORY_POSE, 1); // update sheet frame
                }
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            // if (timeElapsed >= thisFrameTime) {
            if (currFrameTime <= 0.0) {
                if (sprite->getSheet(VICTORY_POSE)->getCurrFr() ==
                    sprite->getSheet(VICTORY_POSE)->getTotalFr() - 1) {
                    // no reset, we want to stay on the last frame basically
                } else {
                    sprite->updateSheet(VICTORY_POSE, 1); // update sheet frame
                }
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
