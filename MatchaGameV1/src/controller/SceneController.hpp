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
#include "ScreenModel.hpp"

class SceneController : public GameController {
public:
    SceneController(GameModel* m, GameView* v, GameController* controller) {
        mainController = controller;
        sceneModel = m;
        view = v;
        exitGame = false;
    };
    // overriding model
    GameModel* getModel() override { return sceneModel; };
    Timer* getSceneTimer() { return sceneTimer; };
    Timer* getGameplayTimer() { return mainController->getGameplayTimer(); };
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
    // So sprites will continue updating according to their states of when this method is called,
    // but no inputs will be handled to update states
    void drawNoInputAnimations(SceneRequest* request);
    // issue with the other impl: the sprites move differently in spite of the same request params.
    // This is due to the system I believe
    // Instead, we need to ensure that, MAYBE 
    void drawNoInputAnimationsV2(SceneRequest* request);
    // yup, yup, the other thing didnt work either which i predicted
    // we should just clamp to a specific posn, this SHOULD be the fix
    void drawNoInputAnimationsV3(SceneRequest* request);
    // this will draw without handling input calls
    void drawWOInput(SceneRequest* request);
    // draws a new rectangle over the screen, initially transparent but soon fades to black
    void drawFadeToBlack(SceneRequest* request);
    // draws a rectangle over the screen, but it eventually becomes transparent and deleted
    void drawFadeOutOfBlack(SceneRequest* request);
    // remove the black screen
    void removeBlackScreen(); // remove black screen
    void addBlackScreen(ScreenModel* screenToSetup);    // add the black screen
    // fades out every sprite in a given list in scene request
    void drawFadeOutSprites(SceneRequest* request);

    void fulfillRequests();
    
protected:
    Timer* sceneTimer = new Timer();
    GameController* mainController; // this is a SEPARATE controller, use only to send game exit requests
    std::deque<SceneRequest*> sceneRequests;
};
