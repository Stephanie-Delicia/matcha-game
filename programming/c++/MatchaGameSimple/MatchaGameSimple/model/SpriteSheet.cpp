// For now, we have that the sheet is already assigned to be the one for a walking Winnie.

#include "SpriteSheet.hpp"
#include <SDL3/SDL.h>
#include <string>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include <iostream>

SpriteSheet::SpriteSheet(int numF, int cF, float width, float height) {
    numFrames = numF;
    currFrame = cF;
    rectWidth = width;
    rectHeight = height;
    std::cout << "\n currFrame in SpriteSheet constructor : " << currFrame;
    std::cout << "\n currFrame in SpriteSheet constructor using function: " << getCurrFrame();
    std::cout << "\n numFrames in SpriteSheet constructor: " << numFrames;
    sheetSrfc = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/chars/animations/winnie/winnie_walk.png");
    std::cout << "\n spriteSheet address in this constructor: " << this << "\n";
}

SpriteSheet::~SpriteSheet() {
    // TODO:
}

SDL_Surface* SpriteSheet::getSheetSrfc() {
    return sheetSrfc; // JTLYK, this is a COPY, not the object itself, not that that is super important for this function.
}

void SpriteSheet::updateFrame() {
    currFrame = currFrame + 1;
    currFrame = currFrame % numFrames;
}

SDL_Rect SpriteSheet::getCurrFrameRect() {
    SDL_Rect srcRect = {static_cast<int> (rectWidth * currFrame),
        0,
        static_cast<int>(rectWidth),
        static_cast<int>(rectHeight)};
    std::cout << "\n currFrame in getCurrFrameRect: " << currFrame;
    // currFrame = currFrame + 1;
    std::cout << "\n currFrame in getCurrFrameRect: " << currFrame;
    // currFrame = currFrame % numFrames;
    std::cout << "\n currFrame in getCurrFrameRect: " << currFrame;
    std::cout << "\n spritesheet address in getCurrFrameRect: " << this;
    return srcRect; // JTLYK, this is a COPY, not the object itself, not that that is super important for this function.
}

int SpriteSheet::getNumFrames() {
    // std::cout << "\n call to getNumFrames() : " << numFrames;
    return numFrames;
}

int SpriteSheet::getCurrFrame() {
    return currFrame;
}

float SpriteSheet::getRectWidth() {
    return rectWidth;
}

float SpriteSheet::getRectHeight() {
    return rectHeight;
}
