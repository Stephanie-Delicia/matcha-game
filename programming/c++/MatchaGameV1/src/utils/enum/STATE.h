#pragma once
#include <stdio.h>

// Enum. class for all animation sheets. A state represents what a sprite is currently doing.
enum STATE {
    IDLE,
    WALKING,
    BLINKING,
    RUNNING,
    DRINKING,
    VICTORY_POSE,
    LOSE_POSE,
    TRANSLATE, // sliding in the x-y plane
    PRESSED,   // texture was clicked on
    HOVER,     // mouse is over a sprite, like as a button
    JUMPING,
    SPEED_BOOST,
    X_WAVE,           // x-movement is in a wave
    SCROLLING_BANNER, // sprite will scroll along its own width
    DIAGONAL_BANNER,  // sprite will scroll along a diagonal line
    NONE              // sprite is not displayed on screen (but may still be on the screen's sprite queues)
};
