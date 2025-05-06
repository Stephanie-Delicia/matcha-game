#pragma once
#include <SDL3/SDL.h>
#include "GameModel.hpp"
#include "GameView.hpp"
/*
    
 */
class GameController {
public:
    GameController(GameModel* m, GameView* v) {
        model = m;
        view = v;
        view->createRenderer();
        view->createWindow(model->getGameName(),
                           model->getWidth(),
                           model->getHeight());
        exitGame = false;
    };
    void draw();
    void update();
    void startGame();
    void handleInput(SDL_Event const &event);
    
private:
    bool exitGame;    // bool for if user exits game window
    GameView*  view;  // Simple controller for only walking a char
    GameModel* model; // Simple model
};
