#pragma once
#include "Request.hpp"

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
