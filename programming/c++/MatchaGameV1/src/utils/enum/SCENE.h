#pragma once
#include <stdio.h>
// Represents possible directions an active sprite can move
enum SCENE {
    FADE,          // draw a black screen on top of the active screen
    UNFADE,        // make the screen on top transparent and then delete it
    STILL,         // just keep drawing the current state of the game w/o updates or input handling
    NO_HANDLING    // just keep drawing and updating, but no user input is taken in
};
