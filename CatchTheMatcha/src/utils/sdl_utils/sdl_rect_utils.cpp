#include <cmath>
#include "Posn.hpp"
#include <SDL3/SDL.h>
#include "sdl_rect_utils.h"

SDL_Rect roundRect(SDL_FRect fRect) {
    // rounds each param in a SDL_FRect to nearest int
    SDL_Rect newRect = {};
    newRect.x = std::round(fRect.x);
    newRect.y = std::round(fRect.y);
    newRect.h = std::round(fRect.h);
    newRect.w = std::round(fRect.w);
    return newRect;
}

bool isPosnOverRect(Posn posn, SDL_FRect rect) {
    float rectHeight = rect.h;
    float rectWidth = rect.w;
    
    bool withinYRange = posn.getY() >= rect.y and posn.getY() <= rect.y + rectHeight;
    bool withinXRange = posn.getX() >= rect.x and posn.getX() <= rect.x + rectWidth;
    
    return (withinYRange and withinXRange);
}

bool isThereRectOverlap(SDL_FRect rect1, SDL_FRect rect2) {
    Posn mPosn = Posn(rect1.x, rect1.y);
    float mHeight = rect1.h;
    float mWidth = rect1.w;
    
    Posn bPosn = Posn(rect2.x, rect2.y);
    float bHeight = rect2.h;
    float bWidth = rect2.w;
    
    // is the first rectangle over the second?
    bool yOverlap = (mPosn.getY() >= bPosn.getY() && mPosn.getY() <= bPosn.getY() + bHeight)  ||
                    (mPosn.getY() + mHeight >= bPosn.getY() && mPosn.getY() + mHeight <= bPosn.getY() + bHeight);
    bool xOverlap = (mPosn.getX() >= bPosn.getX() && mPosn.getX() <= bPosn.getX() + bWidth)  ||
                    (mPosn.getX() + mWidth >= bPosn.getX() && mPosn.getX() + mWidth <= bPosn.getX() + bWidth);
    bool mainOnBoxOverlap = yOverlap && xOverlap;
    // is the second rectangle over the first?
    bool yOverlap2 = (bPosn.getY() >= mPosn.getY() && bPosn.getY() <= mPosn.getY() + mHeight)  ||
                    (bPosn.getY() + bHeight >= mPosn.getY() && bPosn.getY() + bHeight <= mPosn.getY() + mHeight);
    bool xOverlap2 = (bPosn.getX() >= mPosn.getX() && bPosn.getX() <= mPosn.getX() + mWidth)  ||
                    (bPosn.getX() + bWidth >= mPosn.getX() && bPosn.getX() + bWidth <= mPosn.getX() + mWidth);
    bool boxOnMainOverlap = yOverlap2 && xOverlap2;
    
    return (mainOnBoxOverlap || boxOnMainOverlap);
}
