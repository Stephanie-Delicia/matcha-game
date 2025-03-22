#include "SimpleGameModel.hpp"

SimpleGameModel::SimpleGameModel() {
    mainChar = Sprite();
}

SimpleGameModel::~SimpleGameModel() {
    // TODO:
}

void SimpleGameModel::updateCharPosn(float delta_time) {
    mainChar.update(delta_time);
}

void SimpleGameModel::updateCharDir(DIRECTION dir) {
    mainChar.setDirection(dir);
}

DIRECTION SimpleGameModel::getCharDir() {
    return mainChar.getDirection();
}

float SimpleGameModel::getCharXPosn() {
    return mainChar.getXPosn();
}

float SimpleGameModel::getCharYPosn() {
    return mainChar.getYPosn();
}

Sprite SimpleGameModel::getSprite() {
    return mainChar;
}
