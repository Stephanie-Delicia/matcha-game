// Class that represents a Sprite.

#include "Sprite.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "DIRECTION.h"
#include <iostream>
#include "SpriteSheet.hpp"

Sprite::Sprite(SpriteSheet& ss) {
    spriteSrfcLeft = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/chars/animations/winnie/idle_left.png");
    spriteSrfcRight = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/chars/animations/winnie/idle_right.png");
    rect_posn.x = 0;
    rect_posn.y = 0;
    rect_posn.h = 70;
    rect_posn.w = 54;
    
    m_x = 0.0;
    m_y = 266;
    direction = DIRECTION::NONE; // not moving yet
    idleDir = DIRECTION::LEFT;
    
    spriteSheet = &ss;
//    std::cout << "\n sheet frames total in sprite constructor: " << spriteSheet->getNumFrames();
//    std::cout << "\n curr. frame in sprite constructor: " << spriteSheet->getCurrFrame();
//    std::cout << "\n spriteSheet address in sprite constructor: " << spriteSheet;
//    std::cout << "\n sprite address in sprite constructor: " << this << "\n";
}

void Sprite::setDirection(DIRECTION dir) {
    direction = dir;
}

void Sprite::setIdleDir(DIRECTION dir) {
    idleDir = dir;
}

DIRECTION Sprite::getIdleDir() {
    return idleDir;
}

void Sprite::update(float delta_time)
{
    switch(direction)
    {
        case DIRECTION::NONE:
            m_x += 0.0;
            m_y += 0.0;
            break;
        case DIRECTION::UP:
            m_x += 0.0;
            m_y += 0.0;
            break;
        case DIRECTION::DOWN:
            m_x += 0.0;
            m_y += 0.0;
            break;
        case DIRECTION::LEFT:
            m_x = m_x - (5.0 * delta_time);
            break;
        case DIRECTION::RIGHT:
            m_x = m_x + (5.0 * delta_time);
            break;
    }
}

void Sprite::updateSpreadSheetFrameNum()
{
    spriteSheet->updateFrame();
}

void Sprite::resetSpreadSheetFrameNum()
{
    spriteSheet->resetFrame();
}

float Sprite::getXPosn()
{
    return m_x;
}

float Sprite::getYPosn()
{
    return m_y;
}

SDL_Surface* Sprite::getIdleLeft()
{
    return spriteSrfcLeft;
}

SDL_Surface* Sprite::getIdleRight()
{
    return spriteSrfcRight;
}

SpriteSheet* Sprite::getSpriteSheet()
{
    return spriteSheet;
}

DIRECTION Sprite::getDirection()
{
    return direction;
}
