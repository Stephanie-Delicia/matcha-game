#include "SimpleGameModel.hpp"
#include <iostream>

SimpleGameModel::SimpleGameModel(Sprite& s) {
    numFrames = s.getSpriteSheet()->getNumFrames();
    std::cout << "\n numFrames in model constructor: " << numFrames << "\n";
    // std::cout << "\n sprite address in model constructor before assignment: " << &sprite << "\n";
    //std::cout << "\n spriteSheet address in model constructor: " << sprite.getSpriteSheet() << "\n";
    //std::cout << "\n currFrame in SimpleGameModel constructor : " << sprite.getSpriteSheet()->getCurrFrame() << "\n";
    // std::cout << "\n numFrames in SimpleGameModel constructor: " << sprite.getSpriteSheet()->getNumFrames() << "\n";
    mainChar = &s;
    std::cout << "\n numFrames in model constructor: " << numFrames << "\n";
    //std::cout << "\n sprite address in model constructor after assignment: " << mainChar << "\n";
    //std::cout << "\n currFrame in SimpleGameModel constructor : " << mainChar->getSpriteSheet()->getCurrFrame() << "\n";
    //std::cout << "\n numFrames in SimpleGameModel constructor: " << mainChar->getSpriteSheet()->getNumFrames() << "\n";
}

SimpleGameModel::~SimpleGameModel() {
    // TODO:
}

void SimpleGameModel::updateCharPosn(float delta_time) {
    mainChar->update(delta_time);
}

void SimpleGameModel::updateCharDir(DIRECTION dir) {
    mainChar->setDirection(dir);
}

DIRECTION SimpleGameModel::getCharDir() {
    return mainChar->getDirection();
}

float SimpleGameModel::getCharXPosn() {
    return mainChar->getXPosn();
}

float SimpleGameModel::getCharYPosn() {
    return mainChar->getYPosn();
}

Sprite* SimpleGameModel::getSprite() {
    return mainChar;
}
