#include <cmath>
#include "Posn.hpp"

Posn::Posn(float x, float y) {
    xPos = x;
    yPos = y;
}

Posn::Posn() {
    xPos = 0;
    yPos = 0;
}

int Posn::getIntX() {
    return std::round(xPos);
}

int Posn::getIntY() {
    return std::round(yPos);
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
