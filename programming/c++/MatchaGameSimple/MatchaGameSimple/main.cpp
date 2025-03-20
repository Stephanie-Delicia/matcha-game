// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include "global_vars.hpp"
#include "SimpleGameView.hpp"

int main(int argc, char* argv[]) {
    // declare game view and initiate game
    SimpleGameView view;
    view.openGame();
    return 0;
}
