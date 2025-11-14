/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "RunningCommand.hpp"

void RunningCommand::update(Sprite* sprite) {
    DIRECTION stateDir = sprite->getStateDir();
    Posn posn = sprite->getPosn();
    float currFrameTime = sprite->getCurrFrameTime();
    float frameSpeed = sprite->getFrameSpeed() + 2;
    float x = posn.getX();
    float y = posn.getY();
    
    // get sheet width
    SpriteSheet* sheet = sprite->getSheet(sprite->getState());
    float width = sheet->getWidth() / sheet->getTotalFr();
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            if (x >= -width) {
                sprite->setPosn(x - frameSpeed, y);  // update sprite posn
            } else if (x <= - width) {
                sprite->setPosn(screenWidth, y);
            }
            if (currFrameTime <= 0.0) {          // if enough time passed to get to the next frame
                sprite->updateSheet(RUNNING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            if (x <= screenWidth) {
                sprite->setPosn(x + frameSpeed, y);
            } else if (x >= screenWidth) {
                sprite->setPosn(0 - width, y);
            }
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(RUNNING, 1); // update sheet frame
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
