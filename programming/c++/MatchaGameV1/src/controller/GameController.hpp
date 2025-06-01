/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "Timer.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"

class GameController {
public:
    // constructor
    GameController() {
        model = nullptr;
        view = nullptr;
        exitGame = false;
    };
    GameController(GameModel* m, GameView* v) {
        model = m;
        view = v;
        view->createWindow(model->getGameName(),
                           model->getWidth(),
                           model->getHeight());
        exitGame = false;
    };
    // getter
    virtual GameModel* getModel() { return model; };
    // start
    virtual void startGame(); // to be overwritten by more complex games
    // setter
    void setFPS(int fps) { fpsGoal = fps; };
    
protected:
    bool exitGame;
    GameView* view;
    GameModel* model;
    
    // methods for handling events, drawing, and updates
    void draw();
    void update();
    void drawWithFPS();
    void drawWithText(std::string text);
    void gameDelay(float timeElapsed);
    void handleInput(SDL_Event const &event);
    
    // To measure fps
    Timer fpsTimer;
    int fpsGoal = 60;
    int countedFrames = 0;
    std::string fpsText;
    float measureFPS();
    void setFPSText(int fps);
};
