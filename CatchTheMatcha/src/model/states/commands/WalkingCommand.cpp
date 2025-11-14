/*
 A command for handling the walking animation of a character sprite.
 When walking, making it so they loop the screen if they get out of bounds.
 */
#include "WalkingCommand.hpp"

void WalkingCommand::update(Sprite* sprite) {
    DIRECTION stateDir = sprite->getStateDir();
    Posn posn = sprite->getPosn();
    float currFrameTime = sprite->getCurrFrameTime();
    float frameSpeed = sprite->getFrameSpeed();
    float x = posn.getX();
    float y = posn.getY();
    
    // get sheet width
    SpriteSheet* sheet = sprite->getSheet(sprite->getState());
    float width = sheet->getWidth() / sheet->getTotalFr();
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: { // left bound = - sprite width
            if (x >= -width) {
                sprite->setPosn(x - frameSpeed, y);  // update sprite posn
            } else if (x <= - width) {
                sprite->setPosn(screenWidth, y);
            }
            if (currFrameTime <= 0.0) {          // if enough time passed to get to the next frame
                sprite->updateSheet(WALKING, 1); // update sheet frame
            }
            break;
        }
        case DIRECTION::RIGHT: { // right bound = screen width
            if (x <= screenWidth) {
                sprite->setPosn(x + frameSpeed, y);
            } else if (x >= screenWidth) {
                sprite->setPosn(0 - width, y);
            }
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(WALKING, 1); // update sheet frame
            }
            break;
        }
        default: {
            break;
        }
    }
}
