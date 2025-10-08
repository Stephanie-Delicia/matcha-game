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
    
    std::deque<STATE> stateQueue = sprite->getStates();
    auto find_iterator = std::find(stateQueue.begin(), stateQueue.end(), X_WAVE);
    bool has_x_wave_form = (find_iterator != stateQueue.end());
    
    if (startTime == 0 and has_x_wave_form) {
        startTime = timer->getTicks();
    }
    
    // either x changes by a game step or by time from the gameplay timer
    // the game step can be inconsistent, sooooooooooo, definitely by the timer
    
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
            if (has_x_wave_form) {
                sprite->setPosn(xWavePosn(timer->getTicks() - startTime, x), y + frameSpeed); // 
            } else {
                sprite->setPosn(x, y + frameSpeed);
            }
            
            if (currFrameTime <= 0.0) {
                sprite->updateSheet(sprite->getState(), 1);
            }
            break;
        }
    }
}
