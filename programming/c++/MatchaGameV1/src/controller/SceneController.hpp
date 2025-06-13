/*
    A controller that extends the GameController class. Used for drawing game scenes (e.g game instructions, cutscenes). Contains a queue of scene requests to draw. A request must contain a time span, timer, and perhaps an enum for the scene type. For example, we can have a fade to black screen transition. Handle_input shouldn't
    be called for certain cutscenes.
 */
#pragma once
#include <deque>
#include <SDL3/SDL.h>
#include "GameView.hpp"
#include "Timer.hpp"
#include "SceneRequest.hpp"
#include "GameController.hpp"

class SceneController : public GameController {
public:
    SceneController(GameModel* m, GameView* v) {
        std::cout << "In SceneController constructor. [SceneController].\n";
        std::cout << "m ptr: " << m << ", [SceneController].\n";
        std::cout << "v ptr: " << v << ", [SceneController].\n";
        sceneModel = m;
        view = v;
        exitGame = false;
    };
    // overriding model
    GameModel* getModel() override { return sceneModel; };
    GameModel* sceneModel;
    
    // setter
    void addRequest(SceneRequest* req);
    void removeRequest(SceneRequest* req);
    
    // getter
    std::deque<SceneRequest*> getRequests() { return sceneRequests; } ;
    
    // info
    bool hasRequests();
    
    // neither handleinput or update are called. Truly a still scene.
    void drawStillScene(SceneRequest* request);
    void fulfillRequests();
    
protected:
    std::deque<SceneRequest*> sceneRequests;
};
