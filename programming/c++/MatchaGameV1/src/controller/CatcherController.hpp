/*
    Extends the GameController class to include calls for generating boxes for the player to catch.
 */
#pragma once
#include <deque>
#include <string>
#include "BoxToCatchState.hpp"
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"
#include "GameModel.hpp"
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
    CatcherGameModel* getModel() override { return catcherModel; };
    CatcherGameModel* catcherModel;
};
