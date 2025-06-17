/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#pragma once
#include <SDL3/SDL.h>
#include "GameView.hpp"
#include "CatcherGameModel.hpp"
#include "GameController.hpp"
class CatcherController : public GameController {
    // constructor
public:
    CatcherController(CatcherGameModel* m, GameView* v) {
        catcherModel = m;
        view = v;
        view->createWindow(catcherModel->getGameName(),
                           catcherModel->getWidth(),
                           catcherModel->getHeight());
        exitGame = false;
    };
    
    void startGame() override;
    void reset() override;
    CatcherGameModel* getModel() override { return catcherModel; };
    CatcherGameModel* catcherModel;
    bool endScreenDisplay = false;
};
