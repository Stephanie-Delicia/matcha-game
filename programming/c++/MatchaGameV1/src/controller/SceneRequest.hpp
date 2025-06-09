/*
    A controller that extends the GameController class. Used for drawing game scenes (e.g game instructions, cutscenes). Contains a queue of scene requests to draw. A request must contain a time span, timer, and perhaps an enum for the scene type. For example, we can have a fade to black screen transition. Handle_input shouldn't
    be called for certain cutscenes.
 */
#pragma once
#include <deque>
#include <SDL3/SDL.h>
#include "GameView.hpp"
#include "Timer.hpp"
#include "SCENE.h"
#include "SceneRequest.hpp"
#include "GameController.hpp"
#include "CatcherGameModel.hpp"

class SceneRequest {
public:
    SceneRequest(SCENE scene, float time) {
        sceneType = scene;
        timeDuration = time;
    };
    
    // setters
    void setTimeDuration(float time) { timeDuration = time; };
    void setSceneType(SCENE type) { sceneType = type; };
    
    // getters
    float getTimeDuration() { return timeDuration; };
    
protected:
    SCENE sceneType;
    float timeDuration;
};
