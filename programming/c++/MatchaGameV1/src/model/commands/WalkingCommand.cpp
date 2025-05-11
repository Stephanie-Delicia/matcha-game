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
            sprite->setPosn(x - frameSpeed, y);  // update sprite posn
            if (currFrameTime <= 0.0) {          // if enough time passed to get to the next frame
                sprite->updateSheet(WALKING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            sprite->setPosn(x + frameSpeed, y);
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(WALKING, 1); // update sheet frame
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
