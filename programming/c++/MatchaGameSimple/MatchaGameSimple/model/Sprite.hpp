#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>
#include "DIRECTION.h"

// Class definition a Sprite.

class Sprite {
    public:
        Sprite();
        ~Sprite() = default;
    
        void update(float delta_time);
        void draw(SDL_Surface *window_surface);
        void setDirection(DIRECTION dir);
        SDL_Surface* getSrfc();
        DIRECTION getDirection();
        float getXPosn();
        float getYPosn();
    
    private:
        DIRECTION    direction;
        SDL_Surface* sprite_srfc;
        SDL_FRect     rect_posn;
        float       m_x;
        float       m_y;
};
