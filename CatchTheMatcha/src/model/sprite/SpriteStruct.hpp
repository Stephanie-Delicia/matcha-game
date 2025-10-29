#pragma once
#include "SpriteSheet.hpp"
#include "SpriteStruct.hpp"
#include "../../utils/Posn.hpp"
#include "../../utils/enums/NAME.h"
#include "../../utils/enums/STATE.h"
#include "../../utils/enums/DIRECTION.h"

typedef struct SpriteStruct {
    NAME name;          // unique sprite name
    Posn posn;          // (x,y). defaults to (0,0)
    STATE state;        // whatever state sprite is in
    DIRECTION dir;      // direction that sprite faces
    SpriteSheet* sheet; // sprite sheet for the current state
} SpriteStruct;
