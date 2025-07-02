#include "Sprite.hpp"
#include <map>
#include <iostream>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteStruct.hpp"
#include "SpriteSheet.hpp"
#include "sdl_rect_utils.h"
#include "CharacterState.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game. Contains information such as name, location, and states such as direction the char is facing.
 */

NAME Sprite::getName() {
    return name;
}

DIRECTION Sprite::getStateDir() {
    return stateDir;
}

STATE Sprite::getState() {
    return state;
}

Posn Sprite::getPosn() {
    return posn;
}

float Sprite::getFrameSpeed() {
    return frameSpeed;
}

float Sprite::getCurrFrameTime() {
    return currFrameTime;
}

void Sprite::setCurrFrameTime(float time) {
    currFrameTime = time;
}

SpriteSheet* Sprite::getSheet(STATE s) {
    // std::cout << "Sprite: " << getName() << ", and state: " << s << " [Sprite]. \n";
    return sheetMap->getSpriteSheet(name, s);
}

NameStateSheetMap* Sprite::getSheetMap() {
    return sheetMap;
}

void Sprite::setSheetMap(NameStateSheetMap* map) {
    sheetMap = map;
}

void Sprite::setDir(DIRECTION newDir) {
    stateDir = newDir;
}

void Sprite::setFrameSpeed(float speed) {
    frameSpeed = speed;
}

void Sprite::setState(STATE newState) {
    state = newState;
}

void Sprite::setStateHandler(SpriteState* state) {
    stateHandler = state;
}

void Sprite::setPosn(float x, float y) {
    posn.setX(x);
    posn.setY(y);
}

void Sprite::updateSheet(STATE state, int delta) {
    SpriteSheet* sheet = getSheet(state);
    int oldFrameNum = sheet->getCurrFr();
    sheet->setFrameNum(oldFrameNum + delta);
}

void Sprite::resetSheet(STATE state) {
    getSheet(state)->setFrameNum(0);
}

void Sprite::handleInput(SDL_Event const &event) {
    stateHandler->handleInput(this, event);
}

void Sprite::draw(SDL_Surface *windowSrfc) {
//    std::cout << "Sprite id: " << this->name << ". [Sprite]\n";
    stateHandler->draw(this, windowSrfc);
}

void Sprite::update() {
    stateHandler->update(this);
}

SpriteStruct Sprite::getData() {
    SpriteSheet* sheet = getSheet(state);
    return {name, posn, state, stateDir, sheet};
}

std::tuple<SDL_Rect, SDL_Rect> Sprite::getSrcAndDest() {
//    std::cout << "get sheet call. [Sprite]\n";
    SpriteSheet* sheet = getSheet(state);
    SDL_Rect frameRect = roundRect(sheet->getFrameRect());
    SDL_Rect destRect = {posn.getIntX(), posn.getIntY(), frameRect.w, frameRect.h};
    return std::make_tuple(frameRect, destRect);
}



void Sprite::addState(STATE s) {
    statesToProcess.push_back(s);
}

void Sprite::clearQueue() {
    statesToProcess.clear();
}

void Sprite::removeState(STATE s) {
    // if found, object is removed
    auto find_iterator = std::find(statesToProcess.begin(), statesToProcess.end(), s);
    if (find_iterator != statesToProcess.end()) {
        statesToProcess.erase(find_iterator);
    }
}

bool Sprite::hasStateInQueue(STATE s) {
    auto find_iterator = std::find(statesToProcess.begin(), statesToProcess.end(), s);
    return (find_iterator != statesToProcess.end());
}
