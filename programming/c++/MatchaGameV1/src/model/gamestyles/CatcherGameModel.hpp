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
    int getBoxLimit()                          { return boxNumLimit; };
    int getBoxesSize()                         { return static_cast<int>(boxes.size()); };
    int getScoreGoal()                         { return scoreGoal; };
    std::deque<Sprite*> getBoxes()             { return boxes; };
    std::deque<CatcherLevelStruct> getLevels() { return levels; };
    // setter
    void setBoxYLimit(float y)                          { boxYLimit = y; };
    void setScoreGoal(int goal)                         { scoreGoal = goal; };
    void setScore(int newScore)                         { score = newScore; };
    void setBoxNumLimit(int lim)                        { boxNumLimit = lim; };
    void setBoxChance(double chance)                    { boxChance = chance; };
    void addLevel(CatcherLevelStruct lvl)              { levels.push_back(lvl); };
    void setLevels(std::deque<CatcherLevelStruct> lvls) { levels = lvls; };
    
    // gameplay
    void update() override {
        screenNav->getMainScreen()->update();
        loopStartScreenMatchas();
    };
    void clearBoxesQueue(); // recurs thru each box, removes them from the queue, and deletes them (for replaying)
    void addBox(Sprite* box);
    void removeBox(Sprite* box);
    void setUpStartScreenMatchas();

    // checks for gameplay
    void generateBox();     // on some chance, generate a box, add to box list, and give to the active screen
    void goToNextLvl();
    void destroyBoxes();    // recur thru each box and, if the box is on a player or at floor, destroy the box.
    bool didPlayerWinLvl();
    void loopStartScreenMatchas();
    
private:
    // row and col were selected based on having each drink on the start screen be in a square
    int score         = 0;
    int scoreGoal     = 5;
    int boxNumLimit   = 100;
    int totalLevels   = 3;
    float boxYLimit   = 336.00; // where does the box land? it should be destroyed after hitting the floor.
    double boxChance  = 0.05;  // Have a 30% chance of generating a box each game loop
    int currentLevel  = 0; // 0 = level 1
    int numRowMatchas = 9; // 0 to 9
    int numColMatchas = 16; // 0 to 6
    
    // lists/deques
    std::deque<Sprite*> boxes;
    std::deque<Sprite*> matchas_start_screen; // does not change once set
    // the list index corresponds to the level. (E.g., index 0 = level 1, index 1 = level 2, ...)
    std::deque<CatcherLevelStruct> levels = {}; // when a level is finished, remove here and add to completedLevels
    std::deque<CatcherLevelStruct> completedLevels = {};

    // state handlers
    IdleState* idleStateHandler = new IdleState();
    BoxToCatchState* boxStateHandler = new BoxToCatchState();
};
