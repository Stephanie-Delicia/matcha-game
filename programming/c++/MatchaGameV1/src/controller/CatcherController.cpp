/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include <vector>
#include "CatcherController.hpp"

void CatcherController::startGame() {
    Posn scorePosn = Posn(10.00, 15.00);
    Posn fpsPosn = Posn(500.00, 15.00);
    bool introFinished = false;
    bool finishedGame = false;
    float startTime;
    float gStartTime;
    float gTimeElapsed = 0.0;
    float endTime;
    float avgFPS;
    float timeElapsed = 0.0;
    view->initSDL();
    fpsTimer.start();
    
    // game step loop
    gStartTime = fpsTimer.getTicks();
    while (!exitGame) {
        std::cout << "Start game loop. [controller]\n";
        startTime = fpsTimer.getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        
//        if (!introFinished) {
//            drawWithText("Collect 20 boxes to win, bish!", Posn(200, 170));
//            if (gTimeElapsed >= 3000) {
//                introFinished = true;
//            }
//            gTimeElapsed = fpsTimer.getTicks() - gStartTime;
//        }
        
//        if (finishedGame) {
//            drawWithText("You won!", Posn(200, 170));
//            endTime = fpsTimer.getTicks();
//            timeElapsed = endTime - startTime;
//            setFPS(30);
//            gameDelay(timeElapsed);
//            ++countedFrames;
//        }
        
//        // call for box generation
//        if (introFinished and !finishedGame) {
//            getModel()->generateBox();
//        }
        
        // getModel()->generateBox();

        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
//            if (introFinished and !finishedGame) {
//                handleInput(event);
//            }
            std::cout << "Handle input loop. [controller]\n";
            handleInput(event);
             
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
//        if (introFinished and !finishedGame) {
            // getModel()->destroyBoxes();
            std::cout << "Update call. [controller]\n";
            update();
            std::cout << "Draw call. [controller]\n";
            drawWithTexts({"Score: " + std::to_string(getModel()->getScore()), fpsText}, {scorePosn, fpsPosn});
            // adjust fps
            endTime = fpsTimer.getTicks();
            timeElapsed = endTime - startTime;
            gameDelay(timeElapsed);
            ++countedFrames;
//        }
        
//        if (getModel()->getScore() >= 20) {
//            finishedGame = true;
//        }
    }

    // quit
    view->quitSDL();
}

