/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#pragma once
#include "Posn.hpp"
#include <string>
#include <SDL3/SDL.h>
#include "Timer.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"

class SceneController; // forward declaration

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
    void setSceneController();
    
protected:
    bool exitGame;
    GameView* view;
    GameModel* model;
    SceneController* sceneController = nullptr;
    
    // methods for handling events, drawing, and updates
    void draw();
    void update();
    void drawWithFPS();
    void handleEvent(); // includes handling input, updating, and drawing
    void drawWithText(std::string text, Posn posn);
    void drawWithTexts(std::vector<std::string> textLs, std::vector<Posn> posnLs); // for multiple texts
    void gameDelay(float timeElapsed); // handles the main game delay as well as sprite delays
    void delay(float time); // handles only the main game delay
    void handleInput(SDL_Event const &event);
    
    // To measure fps
    Timer fpsTimer;
    int fpsGoal = 58;
    int countedFrames = 0;
    std::string fpsText;
    float measureFPS();
    void setFPSText(int fps);
};
