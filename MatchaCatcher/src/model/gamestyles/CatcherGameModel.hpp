/*
    Extends the GameModel class and now includes a field for score tracking.
 */
#pragma once
#include <deque>
#include <string>
#include "BoxToCatchState.hpp"
#include "IdleState.hpp"
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Timer.hpp"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"
#include "GameModel.hpp"
#include "CatcherLevelStruct.hpp"

class CatcherGameModel : public GameModel {
public:
    // constructor
    using GameModel::GameModel;
    // getter
    int getScore()                             { return score; };
    int getBoxLimit()                          { return matchaNumLimit; };
    int getScoreGoal()                         { return getCurrentLvl().pointGoal; };
    int getMochisSize()                        { return static_cast<int>(mochis.size()); };
    int getMatchasSize()                       { return static_cast<int>(matchas.size()); };
    
    std::deque<Sprite*> getMochis()            { return mochis; };
    std::deque<Sprite*> getMatchas()           { return matchas; };
    std::deque<Sprite*> getAllBoxes();
    CatcherLevelStruct getCurrentLvl()         { return levels[currentLevel]; };
    std::deque<CatcherLevelStruct> getLevels() { return levels; };
    
    // setter
    void setBoxYLimit(float y)            { boxYLimit = y; };
    void setScore(int newScore)           { score = newScore; };
    void setScoreGoal(int goal)           { scoreGoal = goal; };
    void setBoxChance(double chance)      { boxChance = chance; };
    void setMochiNumLimit(int lim)        { mochiNumLimit = lim; };
    void setMatchaNumLimit(int lim)       { matchaNumLimit = lim; };
    void addLevel(CatcherLevelStruct lvl) {
        numLevels++;
        levels.push_back(lvl);
    };
    void setLevels(std::deque<CatcherLevelStruct> lvls) {
        // there should be no issue here since there should never be such a big number of levels
        numLevels = static_cast<int>(lvls.size());
        levels = lvls;
    };
    
    // gameplay
    void update() override {
        // updates sprites and also start screen matchas
        screenNav->getMainScreen()->update();
        loopStartScreenMatchas();
    };
    void clearBoxesQueue();
    void addMochi(Sprite* box);
    void addMatcha(Sprite* box);
    void removeMatcha(Sprite* box);
    void removeMochi(Sprite* box);
    void setUpStartScreenMatchas();

    // checks for gameplay
    
    void generateBox(); // a box is either a matcha or mochi that is falling during gameplay
    void generateMatcha(Posn posn);
    void generateMochi(Posn posn);
    void goToNextLvl();
    void destroyBoxes();
    bool didPlayerWinLvl();
    bool didPlayerLoseLvl(float time);
    void loopStartScreenMatchas(); // updates start screen matchas which are just there for visuals
    
    void setGamePlayTimer(Timer* timer) {gameplayTimer = timer;};
    
private:
    // row and col were selected based on having each drink on the start screen be in a square
    int score         = 0;
    int scoreGoal     = 5;
    int matchaNumLimit = 100;
    int mochiNumLimit = 1;
    int totalLevels   = 3;
    float boxYLimit   = 336.00; // y-posn of the "floor" during gameplay. a falling matcha should be deleted once hitting it
    double boxChance  = 0.06;   // Have a chance of generating a box each game step/loop
    double matchaMochiSplitChance = 0.9;   // 90% of the time when a box is generated, it will be a matcha
    int currentLevel  = 0;      // 0 = level 1
    int numLevels     = 0;
    int maxNumBoostImages = 4;
    float boostDuration   = 10000; // 10 sec
    
    // drawing the matchas on the start screen
    int numRowMatchas = 9;      // 0 to 9
    int numColMatchas = 16;     // 0 to 6
    
    // lists/deques for boxes/levels
    std::deque<Sprite*> matchas;
    std::deque<Sprite*> mochis; // TODO: Need to separate matchas and mochis into separate lists rather than the one above
    std::deque<Sprite*> matchas_start_screen;   // does not change once set
    std::deque<Posn> winnieBoostImagePosns; // will have a max of four posn
    // the list index corresponds to the level. (E.g., index 0 = level 1, index 1 = level 2, ...)
    std::deque<CatcherLevelStruct> levels = {}; // when a level is finished, update currentLevel

    // state handlers, used mainly for start screen matcha display
    IdleState* idleStateHandler = new IdleState();
    BoxToCatchState* boxStateHandler = new BoxToCatchState();
    
    // Timer
    Timer* gameplayTimer;
};
