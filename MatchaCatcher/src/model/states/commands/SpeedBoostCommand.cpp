/*
 A class representing the command for handling the walking state for a sprite.
 */
#include "SpeedBoostCommand.hpp"
#include "Posn.hpp"
#include <iostream>
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "Sprite.hpp"

void SpeedBoostCommand::addTuple(Sprite *sprite) {
    if (images.size() < maxNumImages) {
        // add a tuple of the current sprite state
//        std::cout << "timer->getTicks(): " << timer->getTicks() << ". [SpeedBoostCommand, addTuple()]\n";
//        std::cout << "timeBetweenImage: " << timeBetweenImage << ". [SpeedBoostCommand, addTuple()]\n";
//        std::cout << "lastImageTime: " << lastImageTime << ". [SpeedBoostCommand, addTuple()]\n";
        if (timer->getTicks() - lastImageTime >= timeBetweenImage ) {
//            std::cout << "An image tuple is added! [SpeedBoostCommand, addTuple()]\n";
            std::tuple<Posn, STATE, DIRECTION> newTuple(sprite->getPosn(),
                                                        sprite->getState(),
                                                        sprite->getStateDir());
            if (sprite->getState() != IDLE) {
                images.push_front(newTuple); // push to the front [0 1 2] <--- front
            }
            lastImageTime = timer->getTicks();
           // std::cout << "lastImageTime: " << lastImageTime << ". [SpeedBoostCommand, addTuple()]\n";
        }
    }
}

void SpeedBoostCommand::update(Sprite* sprite) {
    if (!isSpeedBoosted) {
//        std::cout << "Speed is boosted. [SpeedBoostCommand, update()]\n";
//        std::cout << "Speed: " << sprite->getFrameSpeed() << ". [SpeedBoostCommand, update()]\n";
        sprite->setFrameSpeed(sprite->getFrameSpeed() + speedBoost);
//        std::cout << "Speed after boost: " << sprite->getFrameSpeed() << ". [SpeedBoostCommand, update()]\n";
        startTime = timer->getTicks();
        isSpeedBoosted = true;
        images.clear();
//        std::cout << "Initial size images: " << images.size() << ". [SpeedBoostCommand, update()]\n";
    }

    timeElapsed = (timer->getTicks() - startTime); // ms
//    std::cout << "startTime: " << startTime << ". [SpeedBoostCommand, update()]\n";
//    std::cout << "timeElapsed: " << timeElapsed << ". [SpeedBoostCommand, update()]\n";
    
    if (timeElapsed >= boostDuration) { // for knowing when to remove this state from the main sprite's queue
        startTime = 0;
        lastImageTime = 0;
        setStateDone(true);
        // empty out all images for now
        images.clear();
    }
    
    // Remove the last state
    // if (!images.empty() and images.size() >= maxNumImages) {
    if ((!images.empty() and images.size() >= maxNumImages) || (!images.empty() and sprite->getState() == IDLE)) {
//        std::cout << "Removing a tuple: " << startTime << ". [SpeedBoostCommand, update()]\n";
        images.pop_back();
    }
}

void SpeedBoostCommand::resetSpeedBoostCommand(Sprite* sprite) {
    // setStateDone(false);
    getImages().clear();
    setIsSpeedBoosted(false);
    lastImageTime = 0;
//    std::cout << "Speed is reset. [SpeedBoostCommand, resetSpeedBoostCommand()]\n";
//    std::cout << "Speed: " << sprite->getFrameSpeed() << ". [SpeedBoostCommand, resetSpeedBoostCommand()]\n";
    sprite->setFrameSpeed(sprite->getFrameSpeed() - speedBoost);
//    std::cout << "Speed: " << sprite->getFrameSpeed() << ". [SpeedBoostCommand, resetSpeedBoostCommand()]\n";
}
