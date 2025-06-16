/*
    A class that is a data container for what to draw on screen.
    The ScreenModel will have two queues of sprites to be drawn.
    The background queue will contain a predefined background to draw, then there is a main queue.
    The order of drawing is first the background queue, then the main queue.
    The main queue will have more interactive sprites.
 
    A ScreenModel will also have an update queue, that is, the sprites that will be updated when
    the game controller calls for updates.
 
    Before starting a game, a screen nav, containing a couple screen models, must be predefined.
 */
#include <map>
#include <string>
#include <deque>
#include <iostream>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"

std::deque<Sprite*> ScreenModel::getMainQ() {
    return mQueue;
}

std::deque<Sprite*> ScreenModel::getUpdateQ() {
    return updateQueue;
}

std::deque<Sprite*> ScreenModel::getBackgroundQ() {
    return bgQueue;
}

void ScreenModel::setType(SCREEN t) {
    screenT = t;
}

void ScreenModel::setWidth(int width) {
    w = width;
}

void ScreenModel::setHeight(int height) {
    h = height;
}

bool ScreenModel::isActive() {
    return active;
}

bool ScreenModel::onScreen(Sprite* sprite) {
    // uses the find() method for finding given object in a deque
    auto find_iterator = std::find(mQueue.begin(), mQueue.end(), sprite);
    return (find_iterator != mQueue.end());
}

bool ScreenModel::inBackground(Sprite* sprite) {
    auto find_iterator = std::find(bgQueue.begin(), bgQueue.end(), sprite);
    return (find_iterator != bgQueue.end());
}

SCREEN ScreenModel::screenType() {
    return screenT;
}

void ScreenModel::activate() {
    active = true;
}

void ScreenModel::deactivate() {
    active = false;
}

void ScreenModel::emptyScreen() {
    mQueue.clear();
}

void ScreenModel::addToUpdate(Sprite* sprite) {
    updateQueue.push_front(sprite);
}

void ScreenModel::addToMain(Sprite *sprite) {
    mQueue.push_front(sprite);
}

void ScreenModel::addToBG(Sprite* sprite) {
    bgQueue.push_front(sprite);
}

void ScreenModel::removeUpdate(Sprite* sprite) {
    auto find_iterator = std::find(updateQueue.begin(), updateQueue.end(), sprite);
    if (find_iterator != updateQueue.end()) {
        updateQueue.erase(find_iterator);
    }
}

void ScreenModel::removeMain(Sprite* sprite) {
    auto find_iterator = std::find(mQueue.begin(), mQueue.end(), sprite);
    if (find_iterator != mQueue.end()) {
        mQueue.erase(find_iterator);
    }
}

void ScreenModel::removeBG(Sprite* sprite) {
    // if found, object is removed
    auto find_iterator = std::find(bgQueue.begin(), bgQueue.end(), sprite);
    if (find_iterator != bgQueue.end()) {
        bgQueue.erase(find_iterator);
    }
}

void ScreenModel::replaceMain(std::deque<Sprite*> m) {
    mQueue = m;
}

void ScreenModel::replaceUpdate(std::deque<Sprite*> m) {
    updateQueue = m;
}

void ScreenModel::replaceBackground(std::deque<Sprite*> q) {
    bgQueue = q;
}

SDL_Surface* ScreenModel::returnMSurface() {
    return createSurface(mQueue);
}

SDL_Surface* ScreenModel::returnBGSurface() {
    return createSurface(bgQueue);
}

void ScreenModel::update() {
    // recurs thru update queue to apply updates to each sprite
    // draw every sprite in the queue
    for (Sprite* sprite : updateQueue) {
        sprite->update();
    }
}

void ScreenModel::handleInput(const SDL_Event &event) {
    // recurs thru update queue to apply state updates
    // to every sprite in the queue
    for (Sprite* sprite : updateQueue) {
        std::cout << "Sprite to handle input for: " << sprite->getName() << ". [ScreenModel]\n";
        // std::cout << "Sprite ptr: " << sprite << ". [ScreenModel]\n";
        sprite->handleInput(event);
    }
}

SDL_Surface* ScreenModel::createSurface(std::deque<Sprite*> spriteQueue) {
    SDL_Surface* surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_ARGB8888);
    for (Sprite* sprite : spriteQueue) { // draw every sprite in the queue
        std::cout << "Sprite to handle input for: " << sprite->getName() << ". [ScreenModel]\n";
        sprite->draw(surface);
    }
    return surface;
}

void ScreenModel::delayFrameTimes(float gameDelay, float timeElapsed) {
    for (Sprite* sprite : updateQueue) {
        float currFrameTime = sprite->getCurrFrameTime();
        int fpsGoal = sprite->getSheet(sprite->getState())->getFPSGoal();
        float spriteDelay = (1000 / fpsGoal) - timeElapsed - gameDelay;
        if (currFrameTime <= 0.0) {
            sprite->setCurrFrameTime(spriteDelay);
        } else {
            sprite->setCurrFrameTime(currFrameTime - timeElapsed);
        }
    }
}
