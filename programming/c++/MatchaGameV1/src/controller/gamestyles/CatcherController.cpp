/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include <vector>
#include "CatcherController.hpp"
#include "SceneController.hpp"

void CatcherController::startGame() {
    fpsGoal = 55;
    bool startGameplay = false;
    Posn scorePosn = Posn(10.00, 15.00);
    Posn fpsPosn = Posn(500.00, 15.00);
    float startTime;
    float gStartTime;
    float endTime;
    float avgFPS;
    float timeElapsed = 0.0;
    
    fpsTimer = new Timer();
    view->initSDL();
    fpsTimer->start();
    setSceneController();
    
    // game step loop
    gStartTime = fpsTimer->getTicks();
    while (!exitGame) {
        endScreenDisplay = false;
        startTime = fpsTimer->getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        
        if (startGameplay) {
            getModel()->generateBox();
        }
        
        
        // handling events, we first check if there are any scene or navigation requests and fulfill those first.
       if (hasRequests()) {
           handleRequests();
           startGameplay = true;
       } else {
           if (!startGameplay) {
               handleEvents();
           } else {
               // PUT THIS INTO A NEW METHOD INSTEAD
               SDL_Event event;
               while( SDL_PollEvent(&event) )
               {
                   switch( event.type ) {
                       case SDL_EVENT_QUIT:
                           exitGame = true;
                           break;
                   }
               }
               // TODO: MAIN GAMEPLAY NEEDS TO BE CALLED HERE!
               // handleInput(event);
               handleInput(event);
               update();
               drawWithFPS();
           }
           // TODO:
           // HAVE DIFFERENT CALLS - THIS FOR NORMAL SCREENS W/O gameplay
           // FOR GAMEPLAY, WE NEED CONTINUOUS CALLS BASICALLY
          
       }
        
        getModel()->destroyBoxes();
        
        if (getModel()->getScore() >= 5 and !endScreenDisplay) {
            Sprite* replayButtonPtr = getModel()->getNameSpriteMap()->getSprite(REPLAY_BUTTON);
            replayButtonPtr->setState(IDLE);
            addRequest(new SceneRequest(STILL, -1));
            endScreenDisplay = true;
        }
        
        // adjust fps
        endTime = fpsTimer->getTicks();
        timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        countedFrames++;
    }

    // quit
    view->quitSDL();
}

void CatcherController::reset() {
    // reset score
    getModel()->setScore(0);
    // delete all of the boxes
    getModel()->clearBoxesQueue();
    // keep winnie in her location
    // hide replay button again
    Sprite* replayButtonPtr = getModel()->getNameSpriteMap()->getSprite(REPLAY_BUTTON);
    replayButtonPtr->setState(NONE);
    endScreenDisplay = false;
}
