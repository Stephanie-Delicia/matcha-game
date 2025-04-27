#pragma once
#include <stdio.h>

// A class representing a postion, (x, y). Mutable.

class Posn {
public:
    Posn(float x, float y);
    Posn(); // x=0, y=0
    ~Posn();
    
    // getters
    float getX();
    float getY();
    
    // setters
    void setX(float x);
    void setY(float y);
    
private:
    float xPos; // position on the x-axis
    float yPos; // position on the y-axis
};
