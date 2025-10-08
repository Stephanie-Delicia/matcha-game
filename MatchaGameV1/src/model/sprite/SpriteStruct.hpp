#pragma once
#include "SpriteStruct.hpp"
#include "NAME.h"
#include "STATE.h"
#include "DIRECTION.h"
#include "Posn.hpp"
#include "SpriteSheet.hpp"

typedef struct SpriteStruct {
    NAME name;          // unique sprite name
    Posn posn;          // (x,y). defaults to (0,0)
    STATE state;        // whatever state sprite is in
    DIRECTION dir;      // direction that sprite faces
    SpriteSheet* sheet; // sprite sheet for the current state
} SpriteStruct;
