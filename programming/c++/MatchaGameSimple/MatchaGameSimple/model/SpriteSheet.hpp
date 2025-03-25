#pragma once

#include <stdio.h>
#include <SDL3/SDL.h>
#include <string>

// A class for a sprite sheet. Assumes each frame is of the same dimensions.

class SpriteSheet {
    public:
        SpriteSheet(int numF, int cF, float width, float height);
        ~SpriteSheet();
        SDL_Surface* getSheetSrfc();
        void updateFrame();
        int getNumFrames();
        int getCurrFrame();
        float getRectWidth();
        float getRectHeight();
        SDL_Rect getCurrFrameRect(); // current frame surface dims
    
    private:
        int numFrames;      // returns total number of frames in sheet
        int currFrame;      // returns the current frame that is drawn on the window
        float rectWidth;    // width of each frame
        float rectHeight;       // height of each frame
        SDL_Surface* sheetSrfc; // sheet as an SDL surface
};
