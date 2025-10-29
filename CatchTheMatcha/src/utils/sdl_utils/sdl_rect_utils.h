#pragma once
#include <cmath>
#include <SDL3/SDL.h>
#include "../Posn.hpp"

// some useful methods for dealing with Posn and SDL data types

SDL_Rect roundRect(SDL_FRect fRect); // round the floats in a SDL_FRect to ints

bool isThereRectOverlap(SDL_FRect rect1, SDL_FRect rect2); // do these two rectangles overlap?

bool isPosnOverRect(Posn posn, SDL_FRect rect); // is this point on the rectangle?
