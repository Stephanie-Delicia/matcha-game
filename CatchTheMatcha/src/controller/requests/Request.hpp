#pragma once
#include <map>
#include <tuple>
#include <deque>
#include <vector>
#include <string>
#include "../../utils/enums/REQUEST.h"
#include "../../utils/enums/SCENE.h"
#include "../../utils/enums/TIMER.h"
#include "../../utils/Timer.hpp"
#include "../../utils/enums/STATE.h"
#include "../../utils/enums/DIRECTION.h"
#include "../../model/screen/ScreenModel.hpp"
#include "../../model/sprite/Sprite.hpp"

class Request {
public:
    REQUEST getReqType() { return requestType; };
    void setReqType(REQUEST type) { requestType = type; };
    virtual ~Request() {};
private:
    REQUEST requestType;
};
