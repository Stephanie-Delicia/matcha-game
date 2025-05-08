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

SpriteSheet* Sprite::getSheet(STATE s) {
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
    CharacterState stateHandler = CharacterState();
    stateHandler.handleInput(this, event);
}

void Sprite::draw(SDL_Surface *windowSrfc) {
    CharacterState stateHandler = CharacterState();
    stateHandler.draw(this, windowSrfc);
}

void Sprite::update() {
    CharacterState stateHandler = CharacterState();
    stateHandler.update(this);
}

SpriteStruct Sprite::getData() {

    SpriteSheet* sheet = getSheet(state);
    return {name, posn, state, stateDir, sheet};
}

std::tuple<SDL_Rect, SDL_Rect> Sprite::getSrcAndDest() {
    SpriteSheet* sheet = getSheet(state);
    SDL_Rect frameRect = roundRect(sheet->getFrameRect());
    SDL_Rect destRect = {posn.getIntX(), posn.getIntY(), frameRect.w, frameRect.h};
    return std::make_tuple(frameRect, destRect);
}
