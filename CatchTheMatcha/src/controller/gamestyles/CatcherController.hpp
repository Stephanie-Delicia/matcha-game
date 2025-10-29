/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#pragma once
#include <cmath>
#include <vector>
#include <SDL3/SDL.h>
#include "../../view/GameView.hpp"
#include "../../model/gamestyles/CatcherGameModel.hpp"
#include "../GameController.hpp"
#include "../SceneController.hpp"
#include "../../utils/Timer.hpp"
#include "requests/TimerRequest.hpp"

class CatcherController : public GameController {
public:
    // constructor
    CatcherController(CatcherGameModel* m, GameView* v) {
        exitGame = false;
        catcherModel = m;
        view = v;
        view->createWindow(catcherModel->getGameName(),
                           catcherModel->getWidth(),
                           catcherModel->getHeight());
    };
    // overriding methods
    void startGame() override;
    bool isGameBeaten() override { return isLevelWon();};
    bool didPlayerLose() override;
    CatcherGameModel* getModel() override { return catcherModel; };
    
    // game level management
    bool isLevelWon();
    bool isLevelLost(float time);
    void updateLevel(); // this should obtain new level params from the CatcherGameModel
    
    // end game
    void reset() override;
    
protected:
    // params
    float levelStartTime;
    bool initLevelTextDisplayed = false;
    int pointGoal = 5;
    int currLevel = 0;
    bool inGameplay = false;
    float gameplayTime = 0;
    // Catcher controller uses a derived class of a GameModel
    CatcherGameModel* catcherModel;
};
