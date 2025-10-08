#pragma once
#include <stdio.h>
// Represents different scene types
enum SCENE {
    FADE,                // draw a black screen on top of the active screen
    UNFADE,              // make the screen on top transparent and then delete it
    STILL,               // just keep drawing the current state of the game w/o updates or input handling
    ONLY_PLAY_UI,        // screen paused, but user can still use buttons on the screen (like the replay button)
    REMOVE_BLACK_SCREEN,
    ADD_BLACK_SCREEN,
    NO_INPUT_HANDLING,
    NO_INPUT_HANDLING_JUST_TRANSLATION,
    FADE_OUT_GIVEN_SPRITES
};
