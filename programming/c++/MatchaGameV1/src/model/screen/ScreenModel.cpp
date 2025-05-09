
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

void ScreenModel::addToMain(Sprite *sprite) {
    mQueue.push_front(sprite);
}

void ScreenModel::addToBG(Sprite* sprite) {
    bgQueue.push_front(sprite);
}

void ScreenModel::removeMain(Sprite* sprite) {
    // if found, object is removed
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

void ScreenModel::replace(std::deque<Sprite*> m) {
    mQueue = m;
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

SDL_Surface* ScreenModel::createSurface(std::deque<Sprite*> spriteQueue) {
    SDL_Surface* surface = SDL_CreateSurface(w, h, SDL_PIXELFORMAT_ARGB8888);
    for (Sprite* sprite : spriteQueue) { // draw every sprite in the queue
        sprite->draw(surface);
    }
    return surface;
}
