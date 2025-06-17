/*
 */
#pragma once
#include "Timer.hpp"
#include "SCENE.h"
#include <string>
#include "Request.hpp"
#include "ScreenModel.hpp"

class SceneRequest : public Request {
public:
    SceneRequest(enum SCENE scene, float time) {
        sceneType = scene;
        timeDuration = time;
        setReqType(SCENE);
    };
    
    SceneRequest(enum SCENE scene, ScreenModel* screen) {
        screenToSetup = screen;
        sceneType = scene;
        timeDuration = 0.0;
        setReqType(SCENE);
    };
    
    // setters
    void setTimeDuration(float time) { timeDuration = time; };
    void setSceneType(enum SCENE type) { sceneType = type; };
    
    // getters
    float getTimeDuration() { return timeDuration; };
    enum SCENE getSceneType() { return sceneType; };
    ScreenModel* getScreenToSetup() { return screenToSetup; };
    
protected:
    ScreenModel* screenToSetup;
    enum SCENE sceneType;
    float timeDuration; // this is the time duration for a still scene or the fade time.
};
