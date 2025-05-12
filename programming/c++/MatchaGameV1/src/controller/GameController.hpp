#pragma once
#include <SDL3/SDL.h>
#include "Timer.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
/*
    
 */
class GameController {
public:
    GameController(GameModel* m, GameView* v) {
        model = m;
        view = v;
        // TODO: This setup of the view should be in its constructor or something. Not hidden here though.
        view->createWindow(model->getGameName(),
                           model->getWidth(),
                           model->getHeight());
        view->createRenderer();
        exitGame = false;
        
    };
    void draw();
    void drawWithFPS();
    void update();
    void updateSpriteTime(float timeElapsed, float timeDelay);
    void startGame();
    void handleInput(SDL_Event const &event);
    
private:
    bool exitGame;    // bool for if user exits game window
    GameView*  view;  // Simple controller for only walking a char
    GameModel* model; // Simple model
    
    // To measure fps
    Timer fpsTimer;
    int fpsGoal = 60;
    int countedFrames = 0;
    
    // for testing
    float measureFPS();
    std::string fpsText; // display text on screen
    
};
