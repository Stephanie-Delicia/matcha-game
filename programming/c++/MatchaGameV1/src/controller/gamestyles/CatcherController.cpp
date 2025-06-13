/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include <vector>
#include "CatcherController.hpp"
#include "SceneController.hpp"

void CatcherController::startGame() {
    fpsGoal = 55;
    Posn scorePosn = Posn(10.00, 15.00);
    Posn fpsPosn = Posn(500.00, 15.00);
    float startTime;
    float gStartTime;
    float endTime;
    float avgFPS;
    float timeElapsed = 0.0;
    bool endScreenDisplay = false;
    
    fpsTimer = new Timer();
    view->initSDL();
    fpsTimer->start();
    setSceneController();
    std::cout << "scene controller ptr: " << sceneController << ", [CatcherController].\n";
    std::cout << "model ptr: " << getModel() << ", [CatcherController].\n";
    
    // game step loop
    gStartTime = fpsTimer->getTicks();
    while (!exitGame) {
        std::cout << "Start game loop. [CatcherController]\n";
        startTime = fpsTimer->getTicks();
        std::cout << "startTime: " << startTime << " [CatcherController]\n";
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        
        getModel()->generateBox();
        
        // for handling events, we first check if there are any scene or navigation requests and fulfill those first.
       if (hasRequests()) {
           std::cout << "Fulfilling requests. [CatcherController]\n";
           handleRequests();
       } else {
           std::cout << "Regular handling of events. [CatcherController]\n";
           handleEvents();
       }
        
        getModel()->destroyBoxes();
        
        if (getModel()->getScore() >= 20 and !endScreenDisplay) {
            addRequest(new SceneRequest(STILL, 5000));
            endScreenDisplay = true;
            // display a replay button
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
