#include "Posn.hpp"

Posn::Posn(float x, float y) {
    xPos = x;
    yPos = y;
}

Posn::Posn() {
    xPos = 0;
    yPos = 0;
}

Posn::~Posn() {
    
}

float Posn::getX() {
    return xPos;
}

float Posn::getY() {
    return yPos;
}

void Posn::setX(float x) {
    xPos = x;
}

void Posn::setY(float y) {
    yPos = y;
}
