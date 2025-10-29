#pragma once
#include "Request.hpp"

class TimerRequest : public Request {
public:
    TimerRequest() {
        setReqType(TIMER);
    };
    
    TimerRequest(enum TIMER timerType, bool p) {
        pause = p;
        type = timerType;
        setReqType(TIMER);
    };
    
    // setter
    void setTimerType(enum TIMER timerType) { type = timerType; };
    void setPause(bool p) { pause = p; };
    
    // getter
    bool getPause() { return pause; };
    enum TIMER getTimerType() { return type; };

protected:
    enum TIMER type;
    bool pause;
};
