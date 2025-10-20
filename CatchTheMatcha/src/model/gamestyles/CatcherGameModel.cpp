#include <cmath>
#include <memory>
#include <random>
#include "CatcherGameModel.hpp"
#include "CatcherLevelStruct.hpp"

bool CatcherGameModel::didPlayerWinLvl() {
    // get the current level
    // compare level goal with current score
    // if equal, game should pause and a "proceed button" should appear, but this should be done at the controller
    CatcherLevelStruct currLvl = getCurrentLvl();
    if (currLvl.pointGoal <= score) {
        return true;
    } else {
        return false;
    }
}

bool CatcherGameModel::didPlayerLoseLvl(float time) {
    // compares times
    CatcherLevelStruct currLvl = getCurrentLvl();
//    std::cout << "currLvl.timeLimit: " << currLvl.timeLimit << "[didPlayerLoseLvl]\n";
//    std::cout << "time: " << time << "[didPlayerLoseLvl]\n";
    if (currLvl.timeLimit <= time) {
        return true;
    } else {
        return false;
    }
}

void CatcherGameModel::goToNextLvl() {
    currentLevel = (currentLevel + 1) % numLevels;
}

void CatcherGameModel::addMatcha(Sprite* box) {
    matchas.push_front(box);
}

void CatcherGameModel::addMochi(Sprite* box) {
    mochis.push_front(box);
}

std::deque<Sprite*> CatcherGameModel::getAllBoxes() {
    std::deque<Sprite*> boxes;
    for (Sprite* sprite : matchas) {
        boxes.push_back(sprite);
    }
    for (Sprite* sprite : mochis) {
        boxes.push_back(sprite);
    }
    return boxes;
}

void CatcherGameModel::generateMatcha(Posn posn) {
    if (matchas.size() < matchaNumLimit) {
        Posn randPosn = posn;
        NAME matchaType = getCurrentLvl().drinkName;
        // NEW is called here - so ensure this new box gets destroyed sometime down the line;
        // boxes should be constantly moving down AND there is a box number limit, so this shouldn't leak.
        // add to box deque and to main and update queue on the active screen.
        Sprite* newBox = new Sprite(matchaType, randPosn, DOWN, TRANSLATE, nameStateSheetMap);
        boxStateHandler->setCommandTimers(gameplayTimer);
        newBox->setStateHandler(boxStateHandler);
        addMatcha(newBox);
        getActiveScreen()->addToMain(newBox);
        getActiveScreen()->addToUpdate(newBox);
    }
}


void CatcherGameModel::generateMochi(Posn posn) {
    std::random_device randSeed;  // a seed source for the random number engine
    std::mt19937 genMochiType(randSeed()); // mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> realDistr1(0.0, 1.0);
    double typeProb = realDistr1(genMochiType);
    
    if (mochis.size() < mochiNumLimit) {
        NAME mochiType;
        if (typeProb <= 0.5) {
            mochiType = STRAWBERRY_MOCHI;
        } else {
            mochiType = MATCHA_MOCHI;
        }
        Posn randPosn = posn;
        Sprite* newBox = new Sprite(mochiType, randPosn, DOWN, TRANSLATE, nameStateSheetMap);
        
        BoxToCatchState* newBoxState = new BoxToCatchState();
        newBoxState->setCommandTimers(gameplayTimer);
        SpriteState* newState = newBoxState;
        
        // need a unique state due to different timer generations
        newBox->setStateHandler(newState);
        
        SDL_SetSurfaceAlphaMod(newBox->getSheet(newBox->getState())->getSrfcL(), 255);
        SDL_SetSurfaceAlphaMod(newBox->getSheet(newBox->getState())->getSrfcR(), 255);
        addMochi(newBox);
        getActiveScreen()->addToMain(newBox);
        getActiveScreen()->addToUpdate(newBox);
        newBox->addState(X_WAVE);
        newBox->setFrameSpeed(4);
    }
}


void CatcherGameModel::generateBox() {
    // so, this will actually generate EITHER a matcha or a MOCHI
    std::random_device randSeed;  // a seed source for the random number engine
    std::mt19937 genMochiOrMatcha(randSeed()); // mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> realDistr1(0.0, 1.0);
    double boxTypeProb = realDistr1(genMochiOrMatcha); // for choosing a matcha or mochi
    
    // create new posn within screen limits
    std::random_device rd;  // a seed source for the random number engine
    std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> realDistr(0.0, 1.0);
    std::uniform_int_distribution<> intDistr(40, static_cast<int>(screenWidth - 40));
    double boxProb = realDistr(gen);
    int randX = intDistr(gen);
    
    // Do we generate a box by chance?
    if (boxProb <= boxChance) {
        // Do we generate a mochi or box?
        if (boxTypeProb <= matchaMochiSplitChance) {
            generateMatcha(Posn(randX, -30));
        } else {
            generateMochi(Posn(randX, -30));
        }
    }
}

void CatcherGameModel::removeMatcha(Sprite* box) {
    auto find_iterator = std::find(matchas.begin(), matchas.end(), box);
    if (find_iterator != matchas.end()) {
        matchas.erase(find_iterator);
    }
}

void CatcherGameModel::removeMochi(Sprite* box) {
    auto find_iterator = std::find(mochis.begin(), mochis.end(), box);
    if (find_iterator != mochis.end()) {
        mochis.erase(find_iterator);
    }
}

void CatcherGameModel::destroyBoxes() {
    // grab the posn and dims of the main char, then compare with box posn to determine if they make contact
    // get floor level
    Sprite* mainChar = getMainPlayer();
    Posn mPosn = mainChar->getPosn();
    STATE mState = mainChar->getState();
    SpriteSheet* mSheet = mainChar->getSheet(mState);
    float mWidth = mSheet->getWidth() / mSheet->getTotalFr();
    float mHeight = mSheet->getHeight();
    
    // have a list of boxes to delete.
    std::deque<Sprite*> boxesToDelete;
    
    std::deque<Sprite*> allBoxes = getAllBoxes();
    
    for (Sprite* sprite : allBoxes) {
        Posn bPosn = sprite->getPosn();
        STATE bState = sprite->getState();

        SpriteSheet* bSheet = sprite->getSheet(bState);
        float bWidth = bSheet->getWidth();
        float bHeight = bSheet->getHeight();
        bool yOverlap = (mPosn.getY() >= bPosn.getY() && mPosn.getY() <= bPosn.getY() + bHeight)  ||
                        (mPosn.getY() + mHeight >= bPosn.getY() && mPosn.getY() + mHeight <= bPosn.getY() + bHeight);
        bool xOverlap = (mPosn.getX() >= bPosn.getX() && mPosn.getX() <= bPosn.getX() + bWidth)  ||
                        (mPosn.getX() + mWidth >= bPosn.getX() && mPosn.getX() + mWidth <= bPosn.getX() + bWidth);
        bool mainOnBoxOverlap = yOverlap && xOverlap;
        
        bool yOverlap2 = (bPosn.getY() >= mPosn.getY() && bPosn.getY() <= mPosn.getY() + mHeight)  ||
                        (bPosn.getY() + bHeight >= mPosn.getY() && bPosn.getY() + bHeight <= mPosn.getY() + mHeight);
        bool xOverlap2 = (bPosn.getX() >= mPosn.getX() && bPosn.getX() <= mPosn.getX() + mWidth)  ||
                        (bPosn.getX() + bWidth >= mPosn.getX() && bPosn.getX() + bWidth <= mPosn.getX() + mWidth);
        bool boxOnMainOverlap = yOverlap2 && xOverlap2;
        // for either both checks
        if (bPosn.getY() + bHeight >= boxYLimit || mainOnBoxOverlap || boxOnMainOverlap) {
            if (mainOnBoxOverlap || boxOnMainOverlap) {
                // if a mochi, then add SPEED_BOOST state to main char, else just increment score
                if (sprite->getName() == STRAWBERRY_MOCHI || sprite->getName() == MATCHA_MOCHI) {
//                    std::cout << "Adding a speed boost from the mochi. [CatcherModel]\n";
                    std::deque<STATE> stateQueue = getMainPlayer()->getStates();
                    auto find_iterator4 = std::find(stateQueue.begin(), stateQueue.end(), SPEED_BOOST);
                    bool has_speed_boost = (find_iterator4 != stateQueue.end());
                    if (!has_speed_boost) {
                        getMainPlayer()->addState(SPEED_BOOST);
                    }
                } else {
                    score += 1;
                }
            }
            // add to delete queue
            boxesToDelete.push_front(sprite);
        }
    }
    
    // delete boxes
    for (Sprite* box : boxesToDelete) {
        // remove from the boxes list, active screen's active deque and update deque
        if (box->getName() == STRAWBERRY_MOCHI || box->getName() == MATCHA_MOCHI) {
            removeMochi(box);
        } else {
            removeMatcha(box);
        }
        
        getActiveScreen()->removeMain(box);
        getActiveScreen()->removeUpdate(box);
        // THEN delete the sprite from existence
        delete box;    // desallocate memory
        box = nullptr; // to avoid dangling pointer
    }
}

void CatcherGameModel::clearBoxesQueue() {
    std::deque<Sprite*> boxesToDelete;
    std::deque<Sprite*> allBoxes = getAllBoxes();
    for (Sprite* box : allBoxes) {
        boxesToDelete.push_front(box);
        if (box->getName() == STRAWBERRY_MOCHI || box->getName() == MATCHA_MOCHI) {
            removeMochi(box);
        } else {
            removeMatcha(box);
        }
    }
    
    for (Sprite* box : boxesToDelete) {
        getActiveScreen()->removeMain(box);
        getActiveScreen()->removeUpdate(box);
        delete box;    // desallocate memory
        box = nullptr; // to avoid dangling pointer
    }
}

void CatcherGameModel::loopStartScreenMatchas() {
    // check each matcha drink,
    // if the drink is a full box outside of the screen, set its new position
    int numDrink = 0;
//    float miniScrnWidth = 250;
//    float miniScrnHeight = 200;
    float padding = 0;
    
    float squareWidth = screenWidth / numColMatchas;
    float squareHeight = screenHeight / numRowMatchas;
    
    padding = squareHeight;
    
//    std::cout << "squareWidth: " << squareWidth << ".\n";
//    std::cout << "squareHeight: " << squareHeight << ".\n";
    
    float drinkWidth = nameStateSheetMap->getSpriteSheet(BETA_MATCHA, IDLE)->getWidth();
    float drinkHeight = nameStateSheetMap->getSpriteSheet(BETA_MATCHA, IDLE)->getHeight();
    
    float maxX = ((numColMatchas + 1) * squareWidth) + (squareWidth / 2) - (drinkWidth / 2) - (2*squareWidth) + padding;
    float maxY = ((numRowMatchas + 1) * squareHeight) + (squareHeight / 2) - (drinkHeight / 2) - (2*squareHeight) + padding;
    
    
//    std::cout << "squareWidth: " << squareWidth << ".\n";
//    std::cout << "squareHeight: " << squareHeight << ".\n";
//
//    std::cout << "maxX: " << maxX << ".\n";
//    std::cout << "maxY: " << maxY << ".\n";
    
    for (Sprite* drink : matchas_start_screen) {
            Posn drinkPosn = drink->getPosn();
            // if outside the screen by a full box!
            if ((drinkPosn.getX() >= maxX)  or (drinkPosn.getY() >= maxY)) {
                // estimate row and col coordinate
                // float xPosn = (cols * squareWidth) + (squareWidth / 2) - (drinkWidth / 2) - squareWidth + padding;
                int appCol = std::round((drinkPosn.getX() - (squareWidth / 2) + (drinkWidth / 2) + (2*squareWidth) - padding) / squareWidth);
                int appRow = std::round((drinkPosn.getY() - (squareHeight / 2) +  (drinkHeight / 2) + (2*squareHeight) - padding) / squareHeight);
                
//                std::cout << "appRow: " << appRow << ".\n";
//                std::cout << "appCol: " << appCol << ".\n";
                
                float newRow;
                float newCol;
                if (appRow > appCol) {
                    newRow = std::abs(appRow - appCol);
                    newCol = 0;
                } else if (appRow < appCol) {
                    newRow = 0;
                    newCol = std::abs(appCol - appRow);
                } else {
                    newRow = 0;
                    newCol = 0;
                }
                
//                std::cout << "newRow: " << newRow << ".\n";
//                std::cout << "newCol: " << newCol << ".\n";
        
                float newX = (newCol * squareWidth ) + (squareWidth / 2) - (drinkWidth / 2) - (2*squareWidth) + padding;
                float newY = (newRow * squareHeight) + (squareHeight / 2) - (drinkHeight / 2) - (2*squareHeight) + padding;
//
//                std::cout << "newX : " << newX << ".\n";
//                std::cout << "newY : " << newY << ".\n";
                
                drink->setPosn(newX, newY);
            }
            numDrink++;
        }
}

void CatcherGameModel::setUpStartScreenMatchas() {
    int rows = 0;
    int cols = 0;
    
//    float miniScrnWidth = 250;
//    float miniScrnHeight = 200;
    float padding = 0;
    
    float squareWidth = screenWidth / numColMatchas; // 640 % 16 = 40
    float squareHeight = screenHeight / numRowMatchas; // 360 % 9 = 40
    
//    std::cout << "squareWidth: " << squareWidth << ".\n";
//    std::cout << "squareHeight: " << squareHeight << ".\n";
    
    padding = squareHeight;
    float angle = std::atan((squareHeight/squareWidth));
    
    float drinkWidth = nameStateSheetMap->getSpriteSheet(BETA_MATCHA, IDLE)->getWidth();
    float drinkHeight = nameStateSheetMap->getSpriteSheet(BETA_MATCHA, IDLE)->getHeight();
    
    while (rows < numRowMatchas + 2) {
        while (cols < numColMatchas + 2) {
            if (!(rows == 0 and cols == numColMatchas + 1) and
                !(rows == 1 and cols == numColMatchas + 1) and
                !(rows == 0 and cols == numColMatchas) and
                !(rows == numRowMatchas and cols == 0)     and
                !(rows == numRowMatchas + 1 and cols == 0) and
                !(rows == numRowMatchas + 1 and cols == 1) and
                !(rows == numRowMatchas + 1) and
                !(cols == numColMatchas + 1)) {

                float xPosn = std::round((cols * squareWidth) + (squareWidth / 2) - (drinkWidth / 2) - (2*squareWidth) + padding);
                float yPosn = std::round((rows * squareHeight) + (squareHeight / 2) - (drinkHeight / 2) - (2*squareHeight) + padding);

                std::cout << "Posn for start screen drink: (" << xPosn << ", " << yPosn << "). And coordinates: " << "(" <<rows << ", " << cols << ") " << "\n";
                    // create matcha drink sprite
                Sprite* newDrink = new Sprite(BETA_MATCHA, Posn(xPosn, yPosn), LEFT, DIAGONAL_BANNER, nameStateSheetMap);
                newDrink->setFrameSpeed(2);
                newDrink->setAngle(angle);
                newDrink->setAlpha(0.15);
                newDrink->setStateHandler(idleStateHandler);
                matchas_start_screen.push_back(newDrink);
                getActiveScreen()->addToBG(newDrink);
                getActiveScreen()->addToUpdate(newDrink);
                }
            cols++;
        }
        cols = 0;
        rows++;
    }
}
