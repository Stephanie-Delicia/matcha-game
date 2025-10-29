/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <deque>
#include <string>
#include <SDL3/SDL.h>
#include "SDL_ttf.h"
#include "../utils/Posn.hpp"
#include "../utils/Timer.hpp"
#include "requests/Request.hpp"
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"
#include "../utils/enums/REQUEST.h"
#include "requests/NavRequest.hpp"
#include "requests/SceneRequest.hpp"
#include "requests/TimerRequest.hpp"


class SceneController; // forward declaration
class SceneRequest;

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
    void pauseGameplayTimer() { gameplayTimer->pause(); };
    void unpauseGameplayTimer() { gameplayTimer->unpause(); };
    bool getPauseGameBool() { return pauseGame; };
    virtual GameModel* getModel() { return model; };
    virtual bool isGameBeaten() { return false; };
    virtual bool didPlayerLose() { return false; };
    bool getEndScene() { return endScene; };
    Timer* getTimer() { return fpsTimer; };
    Timer* getGameplayTimer() { return gameplayTimer; };
    int getFrameCount() { return countedFrames; };
    bool didGameStart() { return gameStartedBool; };
    
    // setter
    void setPauseGameBool(bool pause) { pauseGame = pause; };
    void setEndScene(bool b) { endScene = b; };
    void setFrameCount(int num) { countedFrames = num; };
    void startGameBool() { gameStartedBool = true; };
    
    // start
    virtual void startGame(); // to be overwritten by more complex games
    void endGame() { exitGame = true; };
    void setScreenNav(ScreenNavigator* nav) { screenNav = nav; } ;
    
    void addRequest(Request* request);
    
    bool hasRequests() { return (requests.size() > 0); };
    
    // reset game
    virtual void reset() {}; // to be overwritten by more complex games
    
    // frame count
    void frameCountAdd(int incrementor) { countedFrames = countedFrames + incrementor; } ;
    void gameDelay(float timeElapsed); // handles the main game delay as well as sprite delays
    
protected:
    bool endScene = false;
    bool gameStartedBool = false;
    bool exitGame;
    GameView* view;
    GameModel* model;
    ScreenNavigator* screenNav;
    SceneController* sceneController;
    std::deque<Request*> requests; // includes requests such as navigating to new screen or drawing a scene
    
    // methods for drawing and updates and delays
    void draw();
    void update();
    void updateUI();
    void drawWithFPS();
    void delay(float time); // handles only the main game delay
    void drawWithText(std::string text, Posn posn);
    void drawWithTexts(std::vector<std::string> textLs, std::vector<Posn> posnLs); // for multiple texts
    
    // handling events
    void handleEvents();                            // handles event polling, updates, and draws for ALL sprites
    void handleInput(SDL_Event const &event);       // call to the model to handle input for THIS event for ALL sprites
    void handleWithoutMainSprite(SDL_Event const &event); // handle input for all elements EXCEPT MAIN
    void handleInputForUI(SDL_Event const &event);  // handling input, but only for UI elements
    void handleRequests();                          // handling requests for navigation or drawing scenes
    void handleMainSprite(const SDL_Event &event);  // handling events only for the main sprite
    
    // get
    
    // scene and nav events
    void removeRequest(Request* request); // first removes request from the queue and then DELETES
    
    // setup
    void setSceneController();
    void setFPS(int fps) { fpsGoal = fps; };
    void setTimer(Timer* timer) {fpsTimer = timer;};
    void setGameplayTimer(Timer* timer) {gameplayTimer = timer;};
    
    // To measure fps
    bool               pauseGame = false;
    Timer* fpsTimer;
    Timer* gameplayTimer = new Timer();
    int fpsGoal = 55;
    int countedFrames = 0;
    std::string fpsText;
    float measureFPS();
    void setFPSText(int fps);
};
