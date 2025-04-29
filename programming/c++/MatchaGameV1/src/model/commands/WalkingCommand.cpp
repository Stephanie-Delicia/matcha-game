#include "WalkingCommand.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"
#include "Sprite.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

//WalkingCommand::WalkingCommand() {
//}
//
//WalkingCommand::~WalkingCommand() {
//}

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
            sprite->updateSheet(WALKING, -1);   // update sheet frame
        }
            
        case DIRECTION::RIGHT: {
            sprite->setPosn(x + frameSpeed, y);
            sprite->updateSheet(WALKING, 1);
        }
        case UP: {
            break;
        }
        case DOWN: {
            break;
        }
    }
}
