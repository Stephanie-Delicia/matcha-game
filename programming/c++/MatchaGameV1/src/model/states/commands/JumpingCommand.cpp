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
//    SpriteSheet* sheet = sprite->getSheet(sprite->getState());
//    float width = sheet->getWidth() / sheet->getTotalFr();
    
    timeElapsed = (timer->getTicks() - startTime) / 1000; // convert ms to s
    
//    std::cout << "timeElapsed: " << timeElapsed << ". [JumpingCommand, checking for jumping.]\n";
//    std::cout << "startTime: " << startTime << ". [JumpingCommand, checking for jumping.]\n";
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            float newY = y + (initV * timeElapsed) + (accDueToG / 2) * (timeElapsed) * timeElapsed;
            if (newY > screenFloor) {
                sprite->setPosn(x, screenFloor);
                sprite->setState(IDLE);
                sprite->addState(IDLE);
                startTime = 0;
                isDone = true;
            } else {
                sprite->setPosn(x, newY);  // update sprite posn
            }
            if (currFrameTime <= 0.0) { // if enough time passed to get to the next frame
                sprite->updateSheet(JUMPING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            float newY = y + (initV * timeElapsed) + (accDueToG / 2) * (timeElapsed) * timeElapsed;
            if (newY > screenFloor) {
                sprite->setPosn(x, screenFloor);
                sprite->setState(IDLE);
                sprite->addState(IDLE);
                startTime = 0;
                isDone = true;
            } else {
                sprite->setPosn(x, newY);  // update sprite posn
            }
            if (currFrameTime <= 0.0) {
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
