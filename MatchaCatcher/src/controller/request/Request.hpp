#pragma once
#include "REQUEST.h"

class Request {
public:
    REQUEST getReqType() { return requestType; };
    void setReqType(REQUEST type) { requestType = type; };
    virtual ~Request() {};
private:
    REQUEST requestType;
};
