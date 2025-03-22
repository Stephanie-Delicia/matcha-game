#pragma once

#include "Sprite.hpp"

// Class definition for a simple game view. View only displays one background for entire game.

class SimpleGameModel {
    public:
        SimpleGameModel();
        ~SimpleGameModel();
    
        void updateCharPosn(float delta_time);
        void updateCharDir(DIRECTION dir);
        DIRECTION getCharDir();
        float getCharXPosn();
        float getCharYPosn();
        Sprite getSprite();
    
    private:
        Sprite mainChar;
};
