/*
   
 */
#include <random>
#include "CatcherGameModel.hpp"

void CatcherGameModel::addBox(Sprite* box) {
    boxes.push_front(box);
}

void CatcherGameModel::generateBox() {
    if (boxes.size() < boxNumLimit) {
        // create new posn within screen limits
        std::random_device rd;  // a seed source for the random number engine
        std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
        std::uniform_real_distribution<double> realDistr(0.0, 1.0);
        std::uniform_int_distribution<> intDistr(0, static_cast<int>(screenWidth));
        
        double randNum = realDistr(gen);
        
        if (randNum <= boxChance) { // create a new box sprite
            int randX = intDistr(gen);
            Posn randPosn = Posn(randX, 0);
            // NEW is called here - so ensure this new box gets destroyed sometime down the line;
            // boxes should be constantly moving down AND there is a box number limit, so this shouldn't leak.
            Sprite* newBox = new Sprite(TEST_BOX, randPosn, DOWN, TRANSLATE, nameStateSheetMap);
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

/*
 DEBUGGING:
 std::cout << "box to remove: " << box << " [CatcherGameModel, removeBox()]\n";
 std::cout << "boxes size before removal: " << boxes.size() << " [CatcherGameModel, removeBox()]\n";
 std::cout << "boxes size after: " << boxes.size() << " [CatcherGameModel, removeBox()]\n";
 //        std::cout << "sprite ptr: " << sprite << "[CatcherGameModel, destroyBoxes()]\n";
 //        std::cout << "box state: " << bState << "\n";
 //        std::cout << "box name: " << sprite->getName() << "\n";
 */
