#include "WalkingCommand.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"
#include "Sprite.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

void WalkingCommand::update(Sprite* sprite) {
    DIRECTION stateDir = sprite->getStateDir();
    Posn posn = sprite->getPosn();
    float frameSpeed = sprite->getFrameSpeed();
    float x = posn.getX();
    float y = posn.getY();
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            sprite->setPosn(x - frameSpeed, y); // update sprite posn
            sprite->updateSheet(WALKING, 1);   // update sheet frame
            break;
        }
            
        case DIRECTION::RIGHT: {
            sprite->setPosn(x + frameSpeed, y);
            sprite->updateSheet(WALKING, 1);
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

void WalkingCommand::update(Sprite* sprite, float timeElapsed, float timeDelay) {
    // float timeDelay -> recommended time to delay
    DIRECTION stateDir = sprite->getStateDir();
    Posn posn = sprite->getPosn();
    float currFrameTime = sprite->getCurrFrameTime();
    float frameSpeed = sprite->getFrameSpeed();
    float x = posn.getX();
    float y = posn.getY();
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            sprite->setPosn(x - frameSpeed, y); // update sprite posn
            if (currFrameTime - timeElapsed <= 0.0) {
                sprite->updateSheet(WALKING, 1);   // update sheet frame
                sprite->setCurrFrameTime(timeDelay);
            } else {
                sprite->setCurrFrameTime(currFrameTime - timeElapsed); // just update the time
            }
            
            break;
        }
            
        case DIRECTION::RIGHT: {
            sprite->setPosn(x + frameSpeed, y);
            if (currFrameTime - timeElapsed <= 0.0) {
                sprite->updateSheet(WALKING, 1);   // update sheet frame
                sprite->setCurrFrameTime(timeDelay);
            } else {
                sprite->setCurrFrameTime(currFrameTime - timeElapsed);
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
