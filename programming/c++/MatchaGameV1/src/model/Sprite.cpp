#include "Sprite.hpp"
#include <map>
#include <SDL3/SDL.h>
#include "NAME.h"
#include "DIRECTION.h"
#include "STATE.h"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "SpriteState.hpp"

/*
 A class representing a sprite (char, background texture, etc) in the game. Contains information such as name, location, and states such as direction the char is facing.
 */

Sprite::~Sprite() {
}

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
    stateHandler.handleInput(this, &event);
}

void Sprite::update() {
    stateHandler.update(this);
}

void Sprite::drawSprite(SDL_Surface *windowSrfc) {
    // TODO
}
