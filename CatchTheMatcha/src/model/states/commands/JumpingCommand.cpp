/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "JumpingCommand.hpp"
#include "Posn.hpp"
#include <iostream>
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "Sprite.hpp"

void JumpingCommand::update(Sprite* sprite) {
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
    
    timeElapsed = (timer->getTicks() - startTime) / 1000; // convert ms to s
    
    // 0 = (V * t) + (G / 2) * (t)^2
    // WOW, THAT FORMULA
    // ITS BEEN YEARS!
    // -b +- sqrt(b^2 - 4ac)/2a
    // -b + sqrt(b^2 - 4ac)
    // --------------------
    // 2a
    // a = 1, b = V, c = G/2
    
    float totalTime = (((SDL_sqrtf(initV * initV - (4 * 1 * accDueToG * 0.5))) - initV)/2)/ 100;
    float timePerFrame = (totalTime / sheet->getTotalFr());
    float thisFrameTime = ((sheet->getCurrFr() + 1) * timePerFrame);
   
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            // this is just the formula for the
            float newY = y;
            if (!timer->isPaused()) {
                newY = y + (initV * timeElapsed) + (accDueToG / 2) * (timeElapsed) * timeElapsed;
            }
            
            if (newY > screenFloor) {
                sprite->setPosn(x, screenFloor);
                sprite->setState(IDLE);
                sprite->addState(IDLE);
                startTime = 0;
                isDone = true;
            } else {
                sprite->setPosn(x, newY);  // update sprite posn
            }
            if (timeElapsed >= thisFrameTime) {

                sprite->updateSheet(JUMPING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            float newY = y;
            if (!timer->isPaused()) {
                newY = y + (initV * timeElapsed) + (accDueToG / 2) * (timeElapsed) * timeElapsed;
            }
            
            if (newY > screenFloor) {
                sprite->setPosn(x, screenFloor);
                sprite->setState(IDLE);
                sprite->addState(IDLE);
                startTime = 0;
                isDone = true;
            } else {
                sprite->setPosn(x, newY);  // update sprite posn
            }
            if (timeElapsed >= thisFrameTime) {
                sprite->updateSheet(JUMPING, 1); // update sheet frame
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
