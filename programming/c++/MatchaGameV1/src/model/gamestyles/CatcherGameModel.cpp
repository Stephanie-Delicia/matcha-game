/*
   
 */
#include <random>
#include "CatcherGameModel.hpp"
#include <cmath>

void CatcherGameModel::addBox(Sprite* box) {
    boxes.push_front(box);
}

void CatcherGameModel::generateBox() {
    if (boxes.size() < boxNumLimit) {
        // create new posn within screen limits
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double> realDistr(0.0, 1.0);
        std::uniform_int_distribution<> intDistr(0, static_cast<int>(screenWidth - 20));
        
        double randNum = realDistr(gen);
        
        if (randNum <= boxChance) { // create a new box sprite
            int randX = intDistr(gen);
            Posn randPosn = Posn(randX, 0);
            // NEW is called here - so ensure this new box gets destroyed sometime down the line;
            // boxes should be constantly moving down AND there is a box number limit, so this shouldn't leak.
            Sprite* newBox = new Sprite(BETA_MATCHA, randPosn, DOWN, TRANSLATE, nameStateSheetMap);
            newBox->setStateHandler(boxStateHandler);
            // add to box deque and to main and update queue on the active screen.
            addBox(newBox);
            getActiveScreen()->addToMain(newBox);
            getActiveScreen()->addToUpdate(newBox);
        }
    }
}

void CatcherGameModel::removeBox(Sprite* box) {
    auto find_iterator = std::find(boxes.begin(), boxes.end(), box);
    if (find_iterator != boxes.end()) {
        boxes.erase(find_iterator);
    }
}

void CatcherGameModel::destroyBoxes() {
    // grab the posn and dims of the main char
    // get floor level
    Sprite* mainChar = getMainPlayer();
    Posn mPosn = mainChar->getPosn();
    STATE mState = mainChar->getState();
    SpriteSheet* mSheet = mainChar->getSheet(mState);
    float mWidth = mSheet->getWidth() / mSheet->getTotalFr();
    float mHeight = mSheet->getHeight();
    
    // have a list of boxes to delete.
    std::deque<Sprite*> boxesToDelete;
    
    for (Sprite* sprite : boxes) {
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
                score += 1;
            }
            // add to delete queue
            boxesToDelete.push_front(sprite);
        }
    }
    
    // delete boxes
    for (Sprite* box : boxesToDelete) {
        // remove from the boxes list, active screen's active deque and update deque
        removeBox(box);
        getActiveScreen()->removeMain(box);
        getActiveScreen()->removeUpdate(box);
        // THEN delete the sprite from existence
        delete box;    // desallocate memory
        box = nullptr; // to avoid dangling pointer
    }
}

void CatcherGameModel::clearBoxesQueue() {
    std::deque<Sprite*> boxesToDelete;
    for (Sprite* box : boxes) {
        boxesToDelete.push_front(box);
        removeBox(box);
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
    int rows = 0;
    int cols = 0;
    int numDrink = 0;
    
    float miniScrnWidth = 250;
    float miniScrnHeight = 200;
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
    
    float miniScrnWidth = 250;
    float miniScrnHeight = 200;
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
