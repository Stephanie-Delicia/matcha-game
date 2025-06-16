/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#pragma once
#include <deque>
#include "Posn.hpp"
#include <string>
#include <SDL3/SDL.h>
#include "Timer.hpp"
#include "GameModel.hpp"
#include "GameView.hpp"
#include "request/Request.hpp"

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
    virtual GameModel* getModel() { return model; };
    // start
    virtual void startGame(); // to be overwritten by more complex games
    void endGame() { exitGame = true; };
    void setScreenNav(ScreenNavigator* nav) { screenNav = nav; } ;
    
    void addRequest(Request* request);
    
    bool hasRequests() { return (requests.size() > 0); };
    
protected:
    bool exitGame;
    GameView* view;
    GameModel* model;
    ScreenNavigator* screenNav;
    SceneController* sceneController;
    std::deque<Request*> requests; // includes requests such as navigating to new screen or drawing a scene
    
    // methods for handling events, drawing, and updates
    void draw();
    void update();
    void drawWithFPS();
    void handleEvents(); // includes handling input, updating, and drawing
    void drawWithText(std::string text, Posn posn);
    void drawWithTexts(std::vector<std::string> textLs, std::vector<Posn> posnLs); // for multiple texts
    void gameDelay(float timeElapsed); // handles the main game delay as well as sprite delays
    void delay(float time); // handles only the main game delay
    void handleInput(SDL_Event const &event);
    void handleRequests();
    
    // get
    
    
    // scene and nav events
    void removeRequest(Request* request); // first removes request from the queue and then DELETES
    
    // setup
    void setSceneController();
    void setFPS(int fps) { fpsGoal = fps; };
    void setTimer(Timer* timer) {fpsTimer = timer;};
    
    // To measure fps
    Timer* fpsTimer;
    int fpsGoal = 58;
    int countedFrames = 0;
    std::string fpsText;
    float measureFPS();
    void setFPSText(int fps);
};
