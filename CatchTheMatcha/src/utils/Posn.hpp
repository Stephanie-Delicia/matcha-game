#pragma once
#include <stdio.h>

// A class representing a postion, (x, y)

class Posn {
public:
    Posn(float x, float y);
    Posn(); // x = 0, y = 0
    
    // getters
    float getX();
    float getY();
    
    // setters
    void setX(float x);
    void setY(float y);
    
    // round posn
    int getIntX();
    int getIntY();
    
private:
    float xPos; // position on the x-axis
    float yPos; // position on the y-axis
};
