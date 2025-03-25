// Class that represents a Sprite.

#include "Sprite.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "DIRECTION.h"
#include <iostream>
#include "SpriteSheet.hpp"

Sprite::Sprite(SpriteSheet& ss) {
    sprite_srfc = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/chars/animations/winnie/idle.png");
    rect_posn.x = 0;
    rect_posn.y = 0;
    rect_posn.h = 70;
    rect_posn.w = 54;
    
    m_x = 0.0;
    m_y = 266;
    direction = DIRECTION::NONE; // not moving yet
    
    spriteSheet = &ss;
    std::cout << "\n sheet frames total in sprite constructor: " << spriteSheet->getNumFrames();
    std::cout << "\n curr. frame in sprite constructor: " << spriteSheet->getCurrFrame();
    std::cout << "\n spriteSheet address in sprite constructor: " << spriteSheet;
    std::cout << "\n sprite address in sprite constructor: " << this << "\n";
}

void Sprite::setDirection(DIRECTION dir) {
    // std::cout << "dir: " << dir << " ";
    direction = dir;
}

void Sprite::update(float delta_time)
{
    // std::cout << "direction: " << direction << " ";
    // std::cout << "DIRECTION::RIGHT: " << DIRECTION::RIGHT << " ";
    // std::cout << "dir in char update: " << direction << " ";
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
            // std::cout << "Shift char to right" << " ";
            // std::cout << "m_x before: " << m_x << " ";
            m_x = m_x + (5.0 * delta_time);
            // std::cout << "m_x after: " << m_x << " ";
            break;
    }

//    rect_posn.x = m_x;
//    rect_posn.y = m_y;
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

SDL_Surface* Sprite::getSrfc()
{
    return sprite_srfc;
}

SpriteSheet* Sprite::getSpriteSheet()
{
    return spriteSheet;
}


DIRECTION Sprite::getDirection()
{
    return direction;
}
