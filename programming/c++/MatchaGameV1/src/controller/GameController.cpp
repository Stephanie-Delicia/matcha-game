#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"

void GameController::startGame() {
    // initialize SDL from view
    view->initSDL();
    
    while (!exitGame) {
        // std::cout << "Started a game step. [controller]\n";
        // get events
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
            
        {
            // event interpretation is passed on to the model's sprites
            handleInput(event);
            // similarly, updates are passed to the model
            update();

            switch(event.type) {
            // we'll interpret events here in the controller too, but only for exiting the game
            // for other types of events (mouse, key presses, etc.) this will be
            // interpreted by sprites individually. for this game model, only the player sprite.
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        // Drawing is passed to the view
        draw();
        // TODO; at 200 ms, you notice that quickly changing directions results in a brief idle animation.
        // not sure exactly how to solve that - wshould I decrease the delay time when I am changing directions?
        
        SDL_Delay(100);
    }

    // Clean up
    view->quitSDL();
}

void GameController::update() {
    // controller calls on the model for this
    // TODO: I'll give the model its own update method to make this call more direct
    // TODO: wait, this must be a yes! lol
    // The nav gets all set up, but the model doesn't. Update the model's main player! LOL
    model->getMainPlayer()->update();
}

void GameController::draw() {
    // view draws based on the model's active screen
    // the active screen contains (1) the background to draw on first and (2) extra stuff like the main player sprite
    // TODO: give the model a return function that returns WHAT should get drawn
    // again, for better readability
    view->draw(model->getActiveScreen());
}

void GameController::handleInput(SDL_Event const &event) {
    // using the model, the game controller will choose which sprites have to interpret events
    // rather than making the model select who gets this call, we'll leave it here with the controller
    //TODO: I'll give the model its own method to make this call more direct
    model->getMainPlayer()->handleInput(event);
}
