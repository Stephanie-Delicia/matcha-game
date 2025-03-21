#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include "global_vars.hpp"
#include "SimpleGameView.hpp"
#include "SimpleController.hpp"
#include "SimpleGameModel.hpp"

// Using SDL3 to create a simple program for moving a sprite around.

int main(int argc, char* argv[]) {
    // declare game model, view, and controller to initiate game
    SimpleGameModel model;
    SimpleGameView view;
    SimpleController controller(model, view);
    controller.openGame();
    return 0;
}
