/*
 */
#pragma once
#include "Request.hpp"

class SceneRequest : public Request {
public:
    SceneRequest(enum SCENE scene, float time) {
        sceneType = scene;
        timeDuration = time;
        setReqType(SCENE);
    };
    
    SceneRequest(enum SCENE scene, float time, std::vector<std::string> strLs, std::vector<Posn> strPosnLs) {
        sceneType = scene;
        timeDuration = time;
        setReqType(SCENE);
        textLs = strLs;
        textPosnLs = strPosnLs;
    };
    
    SceneRequest(enum SCENE scene, ScreenModel* screen) {
        screenToSetup = screen;
        sceneType = scene;
        timeDuration = 0.0;
        setReqType(SCENE);
    };
    
    SceneRequest(enum SCENE scene, std::deque<Sprite*> sprites, float time) {
        // constructor to be used for fading out a list of sprites
        sceneType = scene;
        timeDuration = time;
        setReqType(SCENE);
        spritesToDraw = sprites;
    };
    
    // setters
    void setTimeDuration(float time) { timeDuration = time; };
    void setSceneType(enum SCENE type) { sceneType = type; };
    void setAnimMap(std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> animMap) { animMapQueue = animMap; };
    
    // getters
    float getTimeDuration() { return timeDuration; };
    enum SCENE getSceneType() { return sceneType; };
    std::deque<Sprite*> getSpritesToFadeOut() { return spritesToDraw; };
    ScreenModel* getScreenToSetup() { return screenToSetup; };
    std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> getAnimMap() { return animMapQueue; };
    std::vector<std::string> getTextLs() { return textLs; };
    std::vector<Posn> getTextPosnLs() { return textPosnLs; };
    
    // bool
    bool hasText() { return textLs.size() > 0; };
    
protected:
    // We got here a bit of a pickle
    // So for animation sequences, I could multiple actions for one sprite alone
    // So we have a map that has, first, the sprite as a key, then
    // that gives us the queue of different animation sequences of that sprite
    // We basically want to go over a list of the keys
    // For each key we want to fulfill the list of tuples
    // When the deque is empty, remove the key
    // We terminate the entire sequence when the list of keys is 0
    // the 2nd tuple float param is the time duration for the anim, 1st if the sheet speed
    std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> animMapQueue;
    // a sprite list
    std::deque<Sprite*> spritesToDraw;
    ScreenModel* screenToSetup;
    enum SCENE sceneType;
    float timeDuration; // this is the time duration for a still scene or the fade time.
    std::vector<std::string> textLs;
    std::vector<Posn> textPosnLs;
};
