/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include "CatcherController.hpp"

void CatcherController::startGame() {
    float startTime;
    float endTime;
    float avgFPS;
    float timeElapsed;
    std::cout << "model ptr: " << getModel() << " [CatcherController]\n";
    std::cout << "model's nav ptr: " << getModel()->getNavigator() << " [CatcherController]\n";
    view->initSDL();
    fpsTimer.start();
    
    // game step loop
    while (!exitGame) {
        std::cout << "Game loop. There are " << getModel()->getBoxesSize() << " boxes" << "\n";
        startTime = fpsTimer.getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        // setFPSText(model->getScore());
        
        // call for box generation
        getModel()->generateBox();
        
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            handleInput(event);

            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        getModel()->destroyBoxes();
        update();
        drawWithText("Score: " + std::to_string(getModel()->getScore()));
        
        // adjust fps
        endTime = fpsTimer.getTicks();
        timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        ++countedFrames;
    }

    // quit
    view->quitSDL();
}

