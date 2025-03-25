#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>
#include "DIRECTION.h"
#include "SpriteSheet.hpp"

// Class definition a Sprite.

class Sprite {
    public:
        Sprite(SpriteSheet& ss);
        ~Sprite() = default;
    
        void update(float delta_time);
        void setDirection(DIRECTION dir);
        void updateSpreadSheetFrameNum();
        void resetSpreadSheetFrameNum();
        SDL_Surface* getSrfc(); // the idle surface
        DIRECTION getDirection();
        float getXPosn();
        float getYPosn();
        SpriteSheet* getSpriteSheet();
    
    private:
        SpriteSheet* spriteSheet;
        DIRECTION    direction;
        SDL_Surface* sprite_srfc;
        SDL_FRect    rect_posn;
        float        m_x;
        float        m_y;
};
