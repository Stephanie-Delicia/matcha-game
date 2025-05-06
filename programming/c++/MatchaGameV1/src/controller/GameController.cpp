#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"

void GameController::startGame() {
    // initialize SDL from the view
    view->initSDL();
    
    while (!exitGame) {
        SDL_Event event; // get events
        while(SDL_PollEvent(&event))
        {
            // handle input and update
            handleInput(event);
            update();
            
            // we'll interpret events here too, but only for exiting the game
            // for other types of events (mouse, key presses, etc.) this will be
            // interpreted by sprites individually.
            
            // so, a call to handleInput should be passed to the main sprite for the simplest gameplay
            // similarly, after interpreting and updating to the main sprite, we draw these updates.
            switch(event.type) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        // draw char
        draw();
    }

    // Clean up
    view->quitSDL();
}

void GameController::update() {
    // controller calls on the model for this
    model->getMainPlayer()->update();
}

void GameController::draw() {
    // view draws based on the model's active screen
    // the active screen contains (1) the background to draw on first and (2) extra stuff like the main player sprite
    view->draw(model->getActiveScreen());
}

void GameController::handleInput(SDL_Event const &event) {
    // using the model, the game controller will choose which sprites have to interpret events
    // rather than making the model select who gets this call, we'll leave it here with the controller
    model->getMainPlayer()->handleInput(event);
}
