/*
    Extends the GameModel class and now includes a field for score tracking.
 */
#pragma once
#include <deque>
#include <string>
#include "BoxToCatchState.hpp"
#include <iostream>
#include <SDL3/SDL.h>
#include "SCREEN.h"
#include "Sprite.hpp"
#include "ScreenModel.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "NameStateSheetMap.hpp"
#include "GameModel.hpp"

class CatcherGameModel : public GameModel {
public:
    // constructor
    using GameModel::GameModel;
    // getter
    int getBoxesSize() { return boxes.size(); };
    int getScore() { return score; };
    int getBoxLimit() { return boxNumLimit; };
    int getScoreGoal() { return scoreGoal; };
    std::deque<Sprite*> getBoxes() { return boxes; };
    // setter
    void setScoreGoal(int goal) {scoreGoal = goal;};
    void setScore(int newScore) { score = newScore; };
    void setBoxNumLimit(int lim) { boxNumLimit = lim; };
    void setBoxChance(double chance) { boxChance = chance; };
    void setBoxYLimit(float y) { boxYLimit = y; };
    
    // gameplay
    void addBox(Sprite* box);
    void generateBox(); // on some chance, generate a box, add to box list, and give to the active screen
    void removeBox(Sprite* box);
    void destroyBoxes();    // recur thru each box and, if the box is on a player or at floor, destroy the box.
    void clearBoxesQueue(); // recurs thru each box, removes them from the queue, and deletes them (for replaying)
    
private:
    int scoreGoal = 5;
    int score = 0;
    int boxNumLimit = 100;
    std::deque<Sprite*> boxes;
    double boxChance = 0.05;    // Have a 30% chance of generating a box each game loop
    float boxYLimit = 336.00; // where does the box land? it should be destroyed after hitting the floor.
    BoxToCatchState* boxStateHandler = new BoxToCatchState();
};
