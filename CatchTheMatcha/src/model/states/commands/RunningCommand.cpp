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
    
//    std::cout << "Frame speed: " << frameSpeed << ", and currFrameTime: " << currFrameTime << ". Frame width: " << width << ". Curr frame #: " << sheet->getCurrFr() << ". [RunCmd]\n";
//
//    std::cout << "Screen width: " << screenWidth << ". [RunCmd]\n";
    
    switch (stateDir)
    {
        case DIRECTION::LEFT: {
            if (x - frameSpeed + 6 >= 0) {
                sprite->setPosn(x - frameSpeed, y);  // update sprite posn
            }
            if (currFrameTime <= 0.0) {          // if enough time passed to get to the next frame
                sprite->updateSheet(RUNNING, 1); // update sheet frame
            }
            break;
        }
            
        case DIRECTION::RIGHT: {
            // if ((x + width + frameSpeed) <= screenWidth) {
            if ((x + width - 4) <= screenWidth) {
                sprite->setPosn(x + frameSpeed, y);
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
