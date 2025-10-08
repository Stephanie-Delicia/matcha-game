#pragma once
#include <stdio.h>
// Represents different game "requests" which can ask for navigating to a different screen, animating a scene, or
// pausing the game timer.
enum REQUEST {
    NAVIGATE, // switch screens
    SCENE,    // animation scene (e.g, game pause, game continues but w/o user input, displaying text)
    TIMER     // pausing or unpausing different timers. (e.g, gameplay or global timers)
};
