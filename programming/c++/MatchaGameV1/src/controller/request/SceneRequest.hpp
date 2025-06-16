/*
 */
#pragma once
#include "Timer.hpp"
#include "SCENE.h"
#include "Request.hpp"

class SceneRequest : public Request {
public:
    SceneRequest(enum SCENE scene, float time) {
        sceneType = scene;
        timeDuration = time;
        setReqType(SCENE);
    };
    
    
    // setters
    void setTimeDuration(float time) { timeDuration = time; };
    void setSceneType(enum SCENE type) { sceneType = type; };
    
    // getters
    float getTimeDuration() { return timeDuration; };
    enum SCENE getSceneType() { return sceneType; };
    
protected:
    enum SCENE sceneType;
    float timeDuration;
};
