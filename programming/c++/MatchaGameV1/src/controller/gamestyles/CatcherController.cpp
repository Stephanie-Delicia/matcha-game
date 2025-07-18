/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include <vector>
#include <cmath>
#include "CatcherController.hpp"
#include "SceneController.hpp"

void CatcherController::startGame() {
    fpsGoal = 55;
    bool inGameplay = false;
    Posn scorePosn = Posn(10.00, 15.00);
    Posn fpsPosn = Posn(500.00, 15.00);
    float startTime;
    float gStartTime;
    float endTime;
    float avgFPS;
    float gameTime;
    std::string timeText;
    
    std::string pointsText;
    float timeElapsed = 0.0;
    
    fpsTimer = new Timer();
    view->initSDL();
    fpsTimer->start();
    setSceneController();
    gStartTime = fpsTimer->getTicks();
    
    // game step loop
    while (!exitGame) {
        // fps
        startTime = fpsTimer->getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        
       // polling events, we first check if there are any scene or navigation requests and fulfill those first.
       if (hasRequests()) {
           std::cout << "Fulfilling requests.\n";
           // we give priority to scenes, so if gameplay is 'on' but the menu is opened, then a still animation
           // should play until some user action occurs
           handleRequests();
           startTime = fpsTimer->getTicks();
       } else {
           SDL_Event event;
           while( SDL_PollEvent(&event) )
           {
               handleWithoutMainSprite(event);
               switch( event.type ) {
                   case SDL_EVENT_QUIT:
                       inGameplay = false;
                       exitGame = true;
                       break;
               }
           }
           if (inGameplay) {
               handleMainSprite(event);
           }
           update();
           pointsText = "Score: " + std::to_string(getModel()->getScore());
           gameTime = fpsTimer->getTicks() / 1000;
           timeText = std::to_string(gameTime);
           // Posn(10, 15.00)
           drawWithTexts(std::vector<std::string>{fpsText, pointsText, "Time: " + timeText.substr(0,4)},  std::vector<Posn>{Posn(10, 15.00), Posn(10, 35.00), Posn(10, 55.00)});
       }
        
        // we are in gameplay if we are on the right screen and the point goal hasn't been achieved
        if (screenNav->getMainScreen()->screenType() == GAMEPLAY_SCREEN) {
            if (getModel()->getScore() < pointGoal) {
                inGameplay = true;
                getModel()->generateBox();  // randomly generate boxes
                getModel()->destroyBoxes(); // destroy boxes if they are in contact with the player or floor
            } else {
                inGameplay = false;
                Sprite* replayButtonPtr = getModel()->getNameSpriteMap()->getSprite(REPLAY_BUTTON);
                if (replayButtonPtr->getState() != IDLE) {
                    std::cout << "Reached score goal and adding replay still scene request. \n";
                    replayButtonPtr->setState(IDLE);
                    addRequest(new SceneRequest(STILL, -1)); // until we hit replay or exit out
                }
            }
        } else { // on wrong screen, can't be generating boxes on the start screen!
            inGameplay = false;
        }
        
        // adjust fps
        // I need a global timer and frame counter and one each for pausing
        endTime = fpsTimer->getTicks();
        timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        countedFrames++;
    }

    // quit
    view->quitSDL();
}

void CatcherController::reset() {
    /*
        Reset score, keep winnie in the same location, hide replay button again,
        delete all of the boxes.
     */
    getModel()->setScore(0);
    getModel()->clearBoxesQueue();
    Sprite* replayButtonPtr = getModel()->getNameSpriteMap()->getSprite(REPLAY_BUTTON);
    replayButtonPtr->setState(NONE);
}
