//
//  Represents a simple controller for the matcha game. Allows user to walk main char
//  around. Switched between main chars by presing the space bar.
//  You can only move a char left or right, within the screen bounds.

#include "SimpleController.hpp"
#include "SimpleGameView.hpp"
#include "SimpleGameModel.hpp"

SimpleController::SimpleController(SimpleGameModel m, SimpleGameView v) {
    // set given model and view
    model = m;
    view = v;
    exitGame = false;
}

SimpleController::~SimpleController() {
    // TODO:
}

void SimpleController::openGame() {
    
    // initialize SDL from the view
    view.initializeSDL();
    
    while (!exitGame) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                exitGame = true;
            }
        }
    }

    // Close and destroy the window
    view.destroyWindow();

    // Clean up
    view.quitSDL();
}

void SimpleController::charMove(SDL_Event events) {
    // TODO:
}
