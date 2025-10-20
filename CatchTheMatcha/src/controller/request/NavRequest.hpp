#pragma once
#include "SCENE.h"
#include "Request.hpp"
#include "ScreenModel.hpp"

class NavRequest : public Request {
public:
    NavRequest(ScreenModel* screen) {
        screenToNavTo = screen;
        setReqType(NAVIGATE);
    };
    
    // setters
    void setScreenModel(ScreenModel* screen) { screenToNavTo = screen; };
    
    // getters
    ScreenModel* getScreenModel() { return screenToNavTo; };
    
protected:
    ScreenModel* screenToNavTo;
};
