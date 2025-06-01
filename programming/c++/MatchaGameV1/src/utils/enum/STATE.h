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
    NONE // sprite is not on window
};
