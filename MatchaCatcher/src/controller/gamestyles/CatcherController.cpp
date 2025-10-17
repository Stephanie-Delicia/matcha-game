/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#include <vector>
#include <cmath>
#include "CatcherController.hpp"
#include "SceneController.hpp"
#include "TimerRequest.hpp"

void CatcherController::startGame() {
    fpsGoal = 55;
    bool inGameplay = false;
    
    Posn scorePosn = Posn(10.00, 15.00);
    Posn fpsPosn = Posn(500.00, 15.00);
    float startTime;
    levelStartTime = 0;
    float endTime;
    float avgFPS;
    std::string timeText;
    
    std::string pointsText;
    float timeElapsed = 0.0;
    
    fpsTimer = new Timer();
    view->initSDL();
    fpsTimer->start();
    gameplayTimer->start();
    gameplayTimer->pause();
    setSceneController();
    initLevelTextDisplayed = false;
    
    // game step loop
    while (!exitGame) {
        // fps
        startTime = fpsTimer->getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        SCREEN currScreen = screenNav->getMainScreen()->screenType();
        
        //std::cout << "pauseGame? " << pauseGame << ". [catcher controller.]\n";
        if (pauseGame and !hasRequests()) {
            gameplayTimer->pause();
//            std::cout << "is gameplay timer paused in pause If loop?: " << gameplayTimer->isPaused() << ". [CatcherController]\n";
        } else if (!pauseGame and gameplayTimer->isPaused() and screenNav->getMainScreen()->screenType() == GAMEPLAY_SCREEN) {
            gameplayTimer->unpause();
        }
        
        // take a new level start time when you start a new gameplay
        // this occurs when (1) you haven't won but you also (2) haven't lost and finally (3) level hasnt initialized
        if (!initLevelTextDisplayed and !isLevelWon() and !isLevelLost(gameplayTime)) {
            levelStartTime = fpsTimer->getTicks();
        }
        
       // polling events, we first check if there are any scene or navigation requests and fulfill those first.
        if (hasRequests()) {
//            std::cout << "Fulfilling requests.\n";
            // we give priority to scenes, so if gameplay is 'on' but the menu is opened, then a still animation
            // should play until some user action occurs
            handleRequests();
            startTime = fpsTimer->getTicks(); // reset start time
            if (screenNav->getMainScreen()->screenType() == START_SCREEN) {
                gameplayTimer->pause();
//                std::cout << "At start screen. [catcher controller.]\n";
                pauseGame = false;
//                std::cout << "Unpaused game after handling requests. [catcher controller.]\n";
            } else { // we're on gameplay screen
//                std::cout << "At gameplay screen. [catcher controller.]\n";
                if (isLevelWon() or isLevelLost(gameplayTime)) {
//                    std::cout << "paused game after handling requests. [catcher controller.]\n";
                    pauseGame = true;
                } else {
                    pauseGame = false;
                }
            }

            // there are no requests
       } else {
           // handle/update/draw loop
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
           
           // here is our conundrum
           // we want the gameplay timer to be paused while we go to the start screen from the gameplay
           // However, the fps timer can't be paused, since this is needed for the start screen as well
           
           
           // handle main player
           if (!pauseGame and screenNav->getMainScreen()->screenType() == GAMEPLAY_SCREEN) {
               handleMainSprite(event);
               gameplayTimer->unpause();
               // gameplayTime = (fpsTimer->getTicks() - levelStartTime);
               gameplayTime = gameplayTimer->getTicks();
           }
           update(); // game update
           pointsText = "Score: " + std::to_string(getModel()->getScore());
           timeText = std::to_string(gameplayTime/ 1000);
           
           // draw step
           // always have fps on, but add timer and score for gameplay screen
           if (screenNav->getMainScreen()->screenType() == GAMEPLAY_SCREEN and !pauseGame) {
               if (!initLevelTextDisplayed) {
                   levelStartTime = fpsTimer->getTicks();
                   pauseGame = false;
                   std::string msg = "Catch " + std::to_string(getModel()->getScoreGoal()) + " matchas within " + std::to_string(static_cast<int>(getModel()->getCurrentLvl().timeLimit / 1000)) + " seconds, BISH!";
                   addRequest(new SceneRequest(STILL,
                                               1500,
                                               std::vector<std::string>{msg},
                                               std::vector<Posn>{Posn(180, 75.00)}));
                   initLevelTextDisplayed = true;
                   gameplayTimer->unpause();
               } else {
                   drawWithTexts(std::vector<std::string>{fpsText, pointsText, "Time: " + timeText.substr(0,4)},  std::vector<Posn>{Posn(10, 15.00), Posn(10, 35.00), Posn(10, 55.00)});
               }
           } else {
               drawWithTexts(std::vector<std::string>{fpsText},  std::vector<Posn>{Posn(10, 15.00)});
           }
       }
        
        if (screenNav->getMainScreen()->screenType() == GAMEPLAY_SCREEN and !pauseGame) {
            // determine if player has a speed boost, in case it must be removed for a loss or win.
            std::deque<STATE> stateQueue = getModel()->getMainPlayer()->getStates();
            auto find_iterator4 = std::find(stateQueue.begin(), stateQueue.end(), SPEED_BOOST);
            bool has_speed_boost = (find_iterator4 != stateQueue.end());
            
            if (!isLevelWon()) {
                if (!isLevelLost(gameplayTime)) {
                    getModel()->generateBox();  // randomly generate boxes
                    getModel()->destroyBoxes(); // destroy boxes if they are in contact with the player or floor
                }
                else { // game is lost
                    inGameplay = false;
                    pauseGame = true;
                    Sprite* tryAgainBtnPtr = getModel()->getNameSpriteMap()->getSprite(TRY_AGAIN_BTN);
                    if (tryAgainBtnPtr->getState() != IDLE or !pauseGame) { // AKA, not displayed
                        tryAgainBtnPtr->setState(IDLE);
                        addRequest(new SceneRequest(STILL, -1, std::vector<std::string>{"You lost!"},
                                                    std::vector<Posn>{Posn(180, 75.00)})); // until we hit replay or exit out
//                        std::cout << "Step 2.\n";
                        addRequest(new TimerRequest(GAMEPLAY, true));
//                        std::cout << "Step 1.\n";
                        addRequest(new SceneRequest(NO_INPUT_HANDLING_JUST_TRANSLATION, 2200,
                                                    std::vector<std::string>{"You lost!"},
                                                    std::vector<Posn>{Posn(180, 75.00)}));
                        std::deque<Sprite*> allBoxes = getModel()->getAllBoxes();
//                        std::cout << "All boxes size " << allBoxes.size() << ".\n";
                        addRequest(new SceneRequest(FADE_OUT_GIVEN_SPRITES, allBoxes, 1200));
                        getModel()->getNameSpriteMap()->getSprite(WINNIE)->addState(LOSE_POSE);
                        if (has_speed_boost) {
                            getModel()->getNameSpriteMap()->getSprite(WINNIE)->removeState(SPEED_BOOST);
                            getModel()->getMainPlayer()->getStateHandler()->resetCommands(getModel()->getMainPlayer());
                        }
                    }
                }
            } else { // game is won
//                std::cout << "Won the level! \n";
                inGameplay = false;
                pauseGame = true;
                // gameplayTimer->pause(); // TODO: PUT THIS BEFORE THE SCENE REQUEST
                Sprite* nextLvlBtnPtr = getModel()->getNameSpriteMap()->getSprite(NEXT_LVL_BTN);
                if (nextLvlBtnPtr->getState() != IDLE or !pauseGame) {
                    // std::cout << "Reached score goal and adding replay still scene request. \n";
                    nextLvlBtnPtr->setState(IDLE);
                    addRequest(new SceneRequest(STILL, -1, std::vector<std::string>{"You won! Yay!! Play again?"},
                                                std::vector<Posn>{Posn(160, 75.00)})); // until we hit replay or exit out
//                                            std::cout << "Step 2.\n";
                    addRequest(new TimerRequest(GAMEPLAY, true));
                    addRequest(new SceneRequest(NO_INPUT_HANDLING_JUST_TRANSLATION, 2200, std::vector<std::string>{"Test for victory pose!"},
                                                std::vector<Posn>{Posn(160, 75.00)}));
                    std::deque<Sprite*> allBoxes = getModel()->getAllBoxes();
//                    std::cout << "All boxes size " << allBoxes.size() << ".\n";
                    addRequest(new SceneRequest(FADE_OUT_GIVEN_SPRITES, allBoxes, 1200));
                    getModel()->getNameSpriteMap()->getSprite(WINNIE)->addState(VICTORY_POSE);
                    if (has_speed_boost) {
                        getModel()->getNameSpriteMap()->getSprite(WINNIE)->removeState(SPEED_BOOST);
                        getModel()->getMainPlayer()->getStateHandler()->resetCommands(getModel()->getMainPlayer());
                    }
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
    
    getModel()->clearBoxesQueue();
    NAME drinkName = getModel()->getCurrentLvl().drinkName;
    SpriteSheet* currDrink = getModel()->getNameToSheetMap()->getSpriteSheet(drinkName, TRANSLATE);
    SDL_SetSurfaceAlphaMod(currDrink->getSrfcR(), 255);
    
    if (isLevelWon()) {
//        std::cout << "Player won level.\n";
        updateLevel();
    }
//    std::cout << "Reset called.\n";
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->addState(IDLE);
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->removeState(VICTORY_POSE);
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->updateSheet(VICTORY_POSE, 1);
    
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->removeState(LOSE_POSE);
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->updateSheet(LOSE_POSE, 1);
    
    
    getModel()->getNameSpriteMap()->getSprite(WINNIE)->removeState(SPEED_BOOST);
    // getModel()->getMainPlayer()->getStateHandler()->resetCommands(getModel()->getMainPlayer());
    // we need to reset the speed boost here
    
    getModel()->setScore(0);
    pauseGame = false;
    
    Sprite* nextPtr = getModel()->getNameSpriteMap()->getSprite(NEXT_LVL_BTN);
    Sprite* tryPtr = getModel()->getNameSpriteMap()->getSprite(TRY_AGAIN_BTN);
    nextPtr->setState(NONE);
    tryPtr->setState(NONE);
    gameplayTimer->reset();
    initLevelTextDisplayed = false;
    levelStartTime = fpsTimer->getTicks();
    gameplayTime = 0;
}

bool CatcherController::isLevelWon() {
    // NOTE: this method should be made only when gameplay is on!
    return getModel()->didPlayerWinLvl();
}

bool CatcherController::isLevelLost(float time) {
    // NOTE: this method should be made only when gameplay is on!
    return getModel()->didPlayerLoseLvl(time);
}

bool CatcherController::didPlayerLose() {
    return isLevelLost(gameplayTime);
}

void CatcherController::updateLevel() {
    getModel()->goToNextLvl();
}
