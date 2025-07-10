// Enum. class for all animation sheets.
#pragma once
#include <stdio.h>

enum STATE {
    IDLE,
    WALKING,
    BLINKING,
    RUNNING,
    DRINKING,
    TRANSLATE, // (sliding in the x-y plane, like the geometry term)
    PRESSED,   // texture was clicked on
    HOVER,     // mouse is over the texture
    JUMPING,
    SCROLLING_BANNER, // sprite will scroll along its own width
    DIAGONAL_BANNER, // sprite will scroll along a diagonal line
    NONE // sprite is not on window
};
