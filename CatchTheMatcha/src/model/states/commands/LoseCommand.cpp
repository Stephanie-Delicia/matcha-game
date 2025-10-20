/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "LoseCommand.hpp"
#include "Posn.hpp"
#include <iostream>
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "Sprite.hpp"

void LoseCommand::update(Sprite* sprite) {
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
    
    if (!initialShiftDone and sprite->getStateDir() == LEFT) {
        // this is hardcoded and should occur only once for the first frame
        sprite->setPosn(sprite->getPosn().getX() - 20, sprite->getPosn().getY());
        initialShiftDone = true;
    }
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            if (currFrameTime <= 0.0) {
                if (sprite->getSheet(LOSE_POSE)->getCurrFr() ==
                    sprite->getSheet(LOSE_POSE)->getTotalFr() - 1) {
                    // no reset, we want to stay on the last frame basically
                } else {
                    sprite->updateSheet(LOSE_POSE, 1); // update sheet frame
                }
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            if (currFrameTime <= 0.0) {
                if (sprite->getSheet(LOSE_POSE)->getCurrFr() ==
                    sprite->getSheet(LOSE_POSE)->getTotalFr() - 1) {
                    // no reset, we want to stay on the last frame basically
                } else {
                    sprite->updateSheet(LOSE_POSE, 1); // update sheet frame
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
