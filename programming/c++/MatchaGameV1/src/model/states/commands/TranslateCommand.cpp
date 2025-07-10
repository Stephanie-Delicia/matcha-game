/*
 A class representing the command for translating a sprite in the x or y direction.
 */
#include "TranslateCommand.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"
#include "Sprite.hpp"

void TranslateCommand::update(Sprite* sprite) {
    DIRECTION stateDir  = sprite->getStateDir();
    Posn posn           = sprite->getPosn();
    float currFrameTime = sprite->getCurrFrameTime();
    float frameSpeed    = sprite->getFrameSpeed();
    float x = posn.getX();
    float y = posn.getY();
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            sprite->setPosn(x - frameSpeed, y);    // update sprite posn
            if (currFrameTime <= 0.0) {            // if enough time passed to get to the next frame
                sprite->updateSheet(sprite->getState(), 1); // go to next frame by incrementing frame #
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            sprite->setPosn(x + frameSpeed, y);
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(sprite->getState(), 1);
            }
            break;
        }
        case UP: {
            sprite->setPosn(x, y - frameSpeed);
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(sprite->getState(), 1);
            }
            break;
        }
        case DOWN: {
            sprite->setPosn(x, y + frameSpeed);
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(sprite->getState(), 1);
            }
            break;
        }
    }
}
