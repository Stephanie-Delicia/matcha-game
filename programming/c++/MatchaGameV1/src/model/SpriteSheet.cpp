#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <cmath>
#include "SpriteSheet.hpp"
#include <string>

SpriteSheet::SpriteSheet(std::string filePathL,
                         std::string filePathR,
                         int frames,
                         float width,
                         float height) {
    srfcL = IMG_Load(filePathL.c_str());
    srfcR = IMG_Load(filePathR.c_str());
    currFrame = 0;
    totalFrames = frames;
    w = width;
    h = height;
}

SpriteSheet::SpriteSheet() {
    // sprite sheet without any meaningful data. the surfaces are null pointers.
    srfcL = nullptr;
    srfcR = nullptr;
    currFrame = 0;
    totalFrames = 0;
    w = 0;
    h = 0;
}

SpriteSheet::~SpriteSheet() {
    // TODO:
}

SDL_Surface* SpriteSheet::getSrfcL() {
    return srfcL;
}

SDL_Surface* SpriteSheet::getSrfcR() {
    return srfcR;
}

int SpriteSheet::getTotalFr() {
    return totalFrames;
}

int SpriteSheet::getCurrFr() {
    return currFrame;
}

float SpriteSheet::getWidth() {
    return w;
}

float SpriteSheet::getHeight() {
    return h;
}

SDL_FRect SpriteSheet::getFrameRect() {
    float frameHeight = h;
    float frameWidth = w / totalFrames;
    if (isnan(frameWidth)) { // for blank sprite sheet case
        frameWidth = 0;
    }
    return {currX(), currY(), frameWidth, frameHeight};
}

void SpriteSheet::setFrameNum(int num) {
    // we obtain the modulus for circular frame usage
    // handles when totalFrames = 0
    // also accounts for negative modulo
    if (totalFrames != 0)
    {
        int result = (num) % (totalFrames);
        currFrame = (result + totalFrames) % (totalFrames);
    }
}

float SpriteSheet::currX() {
    // handles NAN results for blank sheets
    float frameW = w / totalFrames;
    float xPoint = frameW * currFrame;
    if (isnan(xPoint))
    {
        return 0;
    }
    else
    {
        return xPoint;
    }
}

float SpriteSheet::currY() {
    return h; // will always be height of entire surface
}
