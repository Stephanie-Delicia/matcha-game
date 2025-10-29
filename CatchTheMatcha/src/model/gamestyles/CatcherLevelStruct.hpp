#pragma once
#include "../../utils/enums/NAME.h"

typedef struct CatcherLevelStruct {
    int level; // starts from 0
    int pointGoal;
    float timeLimit;
    NAME drinkName;
} CatcherLevelStruct;
