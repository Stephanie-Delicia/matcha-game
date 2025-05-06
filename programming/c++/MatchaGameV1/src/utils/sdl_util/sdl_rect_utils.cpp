#include <cmath>
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
