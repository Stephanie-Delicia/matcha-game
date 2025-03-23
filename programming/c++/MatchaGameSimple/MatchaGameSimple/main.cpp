#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include "global_vars.hpp"
#include "SimpleGameView.hpp"
#include "SimpleController.hpp"
#include "SimpleGameModel.hpp"
#include <iostream>

// Using SDL3 to create a simple program for moving a sprite around.

int main(int argc, char* argv[]) {
    // declare game model, view, and controller to initiate game
    SimpleGameModel model;
    SimpleGameView view;
    std::cout << "\n view addressn in main: "  << &view << " ";
    SimpleController controller(model, view);
    // The view is re-instantated for some reason
    controller.openGame();
    return 0;
}
