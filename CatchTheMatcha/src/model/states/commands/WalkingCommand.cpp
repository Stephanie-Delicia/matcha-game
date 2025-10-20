/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "WalkingCommand.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"
#include "Sprite.hpp"

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
        case DIRECTION::LEFT: {
            if (x - frameSpeed + 6 >= 0) {
                sprite->setPosn(x - frameSpeed, y);  // update sprite posn
            }
            if (currFrameTime <= 0.0) {          // if enough time passed to get to the next frame
                sprite->updateSheet(WALKING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            // if ((x + width + frameSpeed) <= screenWidth) {
            if ((x + width - 4) <= screenWidth) {
                sprite->setPosn(x + frameSpeed, y);
            }
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
