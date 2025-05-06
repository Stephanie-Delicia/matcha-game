#pragma once
#include <SDL3/SDL.h>
#include <string>

/*
 A class that represents a sprite sheet. Contains data such as the SDL surface, number of frames, and dims.
 Used for drawing idle textures or player actions. Contains both left facing and right facing pngs as surfaces.
 */

class SpriteSheet {
public:
    SpriteSheet();
    SpriteSheet(std::string filePathL,
                std::string filePathR,
                int frames,
                float width,
                float height);
    
    // getters
    int getTotalFr();         // get total frames
    int getCurrFr();          // current frame
    float getWidth();         // total width
    float getHeight();        // total height
    SDL_Surface* getSrfcL();  // left facing srfc
    SDL_Surface* getSrfcR();  // right facing srfc
    SDL_FRect getFrameRect(); // current rect from the sheet to draw (currX, currY)
    
    // setters
    void setFrameNum(int num);
    
    // for getting each frame's starting coordinates (x,y) on sheet surface
    float currX();
    float currY();
    
private:
    float w; // width
    float h; // height
    int currFrame;
    int totalFrames;
    SDL_Surface* srfcL;
    SDL_Surface* srfcR;
};
