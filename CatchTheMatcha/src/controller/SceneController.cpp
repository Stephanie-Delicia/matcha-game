/*
    A controller that extents the GameController class. Has added functionality for drawing scenes within the game, such as still scenes in which no user input is interpreted and scene transitions such as a fade to
    black.
 */
#include "SceneController.hpp"

void SceneController::drawStillScene(SceneRequest* request) {
//    std::cout << "At drawStillScene" << ". [drawStillScene()]\n";
    if (sceneTimer->isPaused()) {
        sceneTimer->unpause();
    }
    if (!fpsTimer->isPaused()) {
        getGameplayTimer()->pause();
        fpsTimer->pause();
    }
    
    int origFrameCount = mainController->getFrameCount();
    float gStartTime = sceneTimer->getTicks();
    float startTime;
    float timeDuration = request->getTimeDuration();
    
    if (timeDuration <= -1) {
        timeDuration = std::numeric_limits<float>::infinity();
    }
    
    // neither handleinput or update are called. Truly a still scene.
    while ((sceneTimer->getTicks() - gStartTime <= timeDuration) and !mainController->getEndScene()) {
        startTime = sceneTimer->getTicks();
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            handleInputForUI(event);
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        
        if (request->hasText()) {
            drawWithTexts(request->getTextLs(), request->getTextPosnLs());
        } else {
            drawWithText(" ", Posn(200, 170));
        }
        
        updateUI();

        float endTime = sceneTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    if (fpsTimer->isPaused()) {
        getGameplayTimer()->unpause();
        fpsTimer->unpause();
    }
    if (!sceneTimer->isPaused()) {
        sceneTimer->pause();
    }
    mainController->setEndScene(false);
    mainController->setFrameCount(origFrameCount);
    request->setTimeDuration(0);
}

void SceneController::drawFadeToBlack(SceneRequest* request) {
//    std::cout << "At drawFadeToBlack" << ". [drawFadeToBlack()]\n";
    // we have a designated, preloaded rectangle for this. get the sprite
    NameStateSheetMap* stateSheetMap = getModel()->getNameToSheetMap();
    NameSpriteMap* nameSpriteMap = getModel()->getNameSpriteMap();
    // This info isn't  known to someone just using the codebase here but --
    // the black screen only has one state, that is, the IDLE state. So we can directly access it here!
    // default direction state of the sprite should be left
    SpriteSheet* blackScreenSheet = stateSheetMap->getSpriteSheet(BLACK_SCREEN, IDLE);
    // ensure the screen is at 0 transperency first, to fade it in
    uint8_t alpha = 0;
    // 0 = fully transparent
    // get alpha
    bool success = SDL_GetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), &alpha);
    if (success) {
    }
    // make transparent
    if (alpha == 0) {
    } else {
        bool success2 = SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), 0);
    }

    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = getModel()->getActiveScreen()->onScreen(blackScreenPtr);
    
    if (!inQueue) {
        getModel()->getActiveScreen()->addToMain(blackScreenPtr);
    }
    
    if (!getGameplayTimer()->isPaused()) {
        getGameplayTimer()->pause();
    }
    
    float gStartTime = fpsTimer->getTicks();
    float startTime;
    float timeDuration = request->getTimeDuration();
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - gStartTime <= timeDuration) and !mainController->getEndScene()) {
        startTime = fpsTimer->getTicks();
        SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), ((fpsTimer->getTicks() - gStartTime)/timeDuration) * 255.00);
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        drawWithText(" ", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        mainController->frameCountAdd(1);
    }
    if (getGameplayTimer()->isPaused()) {
        getGameplayTimer()->unpause();
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

void SceneController::removeBlackScreen() {
//    std::cout << "At removeBlackScreen" << ". [removeBlackScreen()]\n";
    NameSpriteMap* nameSpriteMap = getModel()->getNameSpriteMap();
    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = getModel()->getActiveScreen()->onScreen(blackScreenPtr);
    
    if (inQueue) {
        getModel()->getActiveScreen()->removeMain(blackScreenPtr);
    }
}

void SceneController::addBlackScreen(ScreenModel* screenToSetup) {
//    std::cout << "At addBlackScreen" << ". [addBlackScreen()]\n";
    NameSpriteMap* nameSpriteMap = getModel()->getNameSpriteMap();
    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = screenToSetup->onScreen(blackScreenPtr);
    
    // ensure the alpha is set to 100%
    NameStateSheetMap* stateSheetMap = getModel()->getNameToSheetMap();
    SpriteSheet* blackScreenSheet = stateSheetMap->getSpriteSheet(BLACK_SCREEN, IDLE);
    bool success = SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), 255);
    
    if (!inQueue) {
        screenToSetup->addToMain(blackScreenPtr);
    }
}

void SceneController::drawFadeOutOfBlack(SceneRequest* request) {
//    std::cout << "At drawFadeOutOfBlack" << ". [drawFadeOutOfBlack()]\n";
    NameStateSheetMap* stateSheetMap = getModel()->getNameToSheetMap();
    NameSpriteMap* nameSpriteMap = getModel()->getNameSpriteMap();
    SpriteSheet* blackScreenSheet = stateSheetMap->getSpriteSheet(BLACK_SCREEN, IDLE);
    uint8_t alpha = 0;
    // 0 = fully transparent
    // get alpha
    bool success = SDL_GetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), &alpha);
    if (success) {
    }
    // make transparent
    if (alpha == 255) {
    } else {
        bool success2 = SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), 255);
    }
    // So, we're going to add that ish to the main screen's queues for drawing
    // Just the main queue! No updates needed.
    // So, we ensure its in the main queue, THEN, we alter the transparency.
    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = getModel()->getActiveScreen()->onScreen(blackScreenPtr);
    
    if (!inQueue) {
        getModel()->getActiveScreen()->addToMain(blackScreenPtr);
    }
    
    if (!getGameplayTimer()->isPaused()) {
        getGameplayTimer()->pause();
    }
    float gStartTime = fpsTimer->getTicks();
    float startTime;
    float timeDuration = request->getTimeDuration();
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - gStartTime <= timeDuration) and !mainController->getEndScene()) {
        startTime = fpsTimer->getTicks();
        SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), (1 - ((fpsTimer->getTicks() - gStartTime)/timeDuration)) * 255.00);
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        drawWithText(" ", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    if (getGameplayTimer()->isPaused()) {
        getGameplayTimer()->unpause();
    }
    SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), 0);
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

bool SceneController::hasRequests() {
    return (sceneRequests.size() > 0);
}

void SceneController::fulfillRequests() {
    std::deque<SceneRequest*> reqsToDelete;
    for (SceneRequest* req : sceneRequests) {
        // fulfill, then add to queue for deletion
        switch (req->getSceneType()) {
            case STILL: {
                drawStillScene(req);
                break;
            }
            
            case NO_INPUT_HANDLING: {
                drawNoInputAnimationsV3(req);
                break;
            }
                
            case NO_INPUT_HANDLING_JUST_TRANSLATION: {
                drawWOInput(req);
                break;
            }
                
            case FADE: {
                drawFadeToBlack(req);
                break;
            }
                
            case UNFADE: {
                drawFadeOutOfBlack(req);
                break;
            }
                
            case FADE_OUT_GIVEN_SPRITES: {
                drawFadeOutSprites(req);
                break;
            }
                
            case REMOVE_BLACK_SCREEN: {
                removeBlackScreen();
                break;
            }
                
            case ADD_BLACK_SCREEN: {
                addBlackScreen(req->getScreenToSetup());
                break;
            }
        
            default: {
                break;
            }

        }
        reqsToDelete.push_front(req);
    }
    
    // delete
    for (SceneRequest* req : reqsToDelete) {
        removeRequest(req);
    }
}

void SceneController::removeRequest(SceneRequest* req) {
    // requests, when created, are dynamically allocated.
    // the deletion will occur in the main controller. Here, we simply remove the ptr from the queue.
    auto find_iterator = std::find(sceneRequests.begin(), sceneRequests.end(), req);
    if (find_iterator != sceneRequests.end()) {
        sceneRequests.erase(find_iterator);
    }
}

void SceneController::addRequest(SceneRequest* req) {
    sceneRequests.push_front(req);
}

void SceneController::drawNoInputAnimations(SceneRequest *request) {
//    std::cout << "At drawNoInputAnimations" << ". [drawNoInputAnimations()]\n";
    float startTime = fpsTimer->getTicks();
    // we want to keep repeating this until the map key list is empty
    std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> animMap = request->getAnimMap();
    
    // polling events
    while (animMap.size() > 0 and !mainController->getEndScene()) {
        startTime = fpsTimer->getTicks();
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            handleInputForUI(event);
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        // get time elapsed
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        /*
         Here we will do the heavy lifting.
         1. Recur thru the map keys [that is, the sprite]. DONE
         2. See if it has a top element for the deque. DONE
         3. If yes, then ensure the sprite has the correct params as indicated in the tuple. DONE.
            - THEN, check if the time duration is up; if it will be at or less than 0, remove that tuple from deque
            - IF NOT, then decrement the time duration by timeElapsed
         4. If no, then remove that sprite from the map
         5. Repeat until map is empty.
         */
        // TODO: remove keys to be removed AFTERWARDS
        std::deque<Sprite*> keysToRemove;
        for (auto& spriteAnim : animMap) {
            // std::deque<std::tuple<STATE, DIRECTION, float, float>> = spriteAnim.second;
            // if the deque is empty, then remove key since we have done all of the animations
            Sprite* currSprite = spriteAnim.first;
            if (spriteAnim.second.size() == 0) { // if all anims were completed, delete key/sprite
                keysToRemove.push_front(spriteAnim.first);
            } else { // otherwise, look at the front of the deque and update accordingly and decrement time duration
                // first element
                std::tuple<STATE, DIRECTION, float, float, float> topAnim = spriteAnim.second.front();
                STATE state = std::get<0>(topAnim);
                DIRECTION dir = std::get<1>(topAnim);
                float speed = std::get<2>(topAnim);
                float timeDur = std::get<3>(topAnim);
                float newTimeDur = timeDur - timeElapsed;
                
                if (newTimeDur <= 0) {
                    // remove this anim from deque
                    spriteAnim.second.pop_front();
                } else {
                    currSprite->setState(state);
                    currSprite->setDir(dir);
                    currSprite->setFrameSpeed(speed);
                    // replace tuple with new tuple time unless the
                    spriteAnim.second[0] = std::tuple<STATE, DIRECTION, float, float, float>(state, dir, speed, newTimeDur, 0);
                }
            }
        }
        
        // delete keys
        for (Sprite* sprite : keysToRemove) {
            animMap.erase(sprite);
        }
        
        drawWithText("TEST", Posn(200, 170));
        update();
        
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

void SceneController::drawNoInputAnimationsV2(SceneRequest *request) {
    // different system, the three floats in order are: speed, x change, y change ALL POSITIVE
    std::cout << "At drawNoInputAnimationsV2" << ". [drawNoInputAnimationsV2()]\n";
    float startTime = fpsTimer->getTicks();
    std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> animMap = request->getAnimMap();
    
    // polling events
    while (animMap.size() > 0 and !mainController->getEndScene()) {
        startTime = fpsTimer->getTicks();
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            handleInputForUI(event);
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        // get time elapsed
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;

        // TODO: remove keys to be removed AFTERWARDS
        std::deque<Sprite*> keysToRemove;
        for (auto& spriteAnim : animMap) {
            // std::deque<std::tuple<STATE, DIRECTION, float, float>> = spriteAnim.second;
            // if the deque is empty, then remove key since we have done all of the animations
            Sprite* currSprite = spriteAnim.first;
            if (spriteAnim.second.size() == 0) { // if all anims were completed, delete key/sprite
                keysToRemove.push_front(spriteAnim.first);
            } else { // otherwise, look at the front of the deque and update accordingly and decrement time duration
                // first element
                std::tuple<STATE, DIRECTION, float, float, float> topAnim = spriteAnim.second.front();
                STATE state = std::get<0>(topAnim);
                DIRECTION dir = std::get<1>(topAnim);
                float speed = std::get<2>(topAnim);
                float xChange = std::get<3>(topAnim);
                //float yChange = std::get<4>(topAnim);
                Posn spritePosn = currSprite->getPosn();
                
                float diff = xChange - speed;
                
                if (diff <= 0) {
                    // remove this anim from deque and clamp to goal
                    if (dir == RIGHT) {
                        currSprite->setPosn(spritePosn.getX() + xChange, spritePosn.getY());
                    } else {
                        currSprite->setPosn(spritePosn.getX() - xChange, spritePosn.getY());
                    }
                    spriteAnim.second.pop_front();
                } else {
                    currSprite->setState(state);
                    currSprite->setDir(dir);
                    currSprite->setFrameSpeed(speed);
                    // replace tuple with new tuple time unless the
                    spriteAnim.second[0] = std::tuple<STATE, DIRECTION, float, float, float>(state, dir, speed, diff, 0);
                }
            }
        }
        
        // delete keys
        for (Sprite* sprite : keysToRemove) {
            animMap.erase(sprite);
        }
        
        drawWithText("TEST 2", Posn(200, 170));
        update();
        
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

void SceneController::drawNoInputAnimationsV3(SceneRequest *request) {
//    std::cout << "At drawNoInputAnimationsV3" << ". [drawNoInputAnimationsV3()]\n";
    // different system, the three floats in order are: speed, x goal
    // the last float is not used actually
    float startTime = fpsTimer->getTicks();
    std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> animMap = request->getAnimMap();

    while (animMap.size() > 0 and !mainController->getEndScene()) {
        startTime = fpsTimer->getTicks();
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            handleInputForUI(event);
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }

        std::deque<Sprite*> keysToRemove; // remove keys to be removed AFTERWARDS
        
        for (auto& spriteAnim : animMap) {
            // if the deque is empty, then remove key since we have done all of the animations
            Sprite* currSprite = spriteAnim.first;
            if (spriteAnim.second.size() == 0) { // if all anims were completed, delete key/sprite
                keysToRemove.push_front(spriteAnim.first);
            } else { // otherwise, look at the front of the deque and update accordingly and decrement time duration
                // first element
                std::tuple<STATE, DIRECTION, float, float, float> topAnim = spriteAnim.second.front();
                STATE state = std::get<0>(topAnim);
                DIRECTION dir = std::get<1>(topAnim);
                float speed = std::get<2>(topAnim);
                float xGoal = std::get<3>(topAnim);
                currSprite->setState(state);
                currSprite->setDir(dir);
                currSprite->setFrameSpeed(speed);
                Posn spritePosn = currSprite->getPosn();
//                std::cout << "Sprite id: " << currSprite->getName() << ". \n";
//                std::cout << "Curr posn: " << spritePosn.getX() << ", " << spritePosn.getY() << ". \n";
//                std::cout << "Curr state: " << currSprite->getState() << ". \n";
//                std::cout << "Curr speed: " << currSprite->getFrameSpeed() << ". \n";
//                std::cout << "xGoal: " << xGoal << ". \n";
                
                float newX;
                float setX;
                float reachedGoal = false;
                if (dir == RIGHT) {
                    newX = spritePosn.getX() + speed;
                    setX = spritePosn.getX() - speed;
                    reachedGoal = (newX >= xGoal);
                } else {
                    newX = spritePosn.getX() - speed;
                    setX = spritePosn.getX() + speed;
                    reachedGoal = (newX <= xGoal);
                }
                
                // std::cout << "reachedGoal: " << reachedGoal << ". \n";
                
                if (state == TRANSLATE) {
                    if (reachedGoal) {
                        // remove this anim from deque and clamp to goal
                        currSprite->setPosn(xGoal, spritePosn.getY());
                        currSprite->setFrameSpeed(0);
                        spriteAnim.second.pop_front();
                    } else {
                        // replace tuple with new tuple time unless the
                        spriteAnim.second[0] = std::tuple<STATE, DIRECTION, float, float, float>(state, dir, speed, xGoal, 0);
                    }
                } else {
                    spriteAnim.second.pop_front();
                }

            }
        }
        
        // delete keys
        for (Sprite* sprite : keysToRemove) {
            animMap.erase(sprite);
        }
        
        drawWithText(" ", Posn(200, 170));
        update();
        
        // get time elapsed
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
//        std::cout << "timeElapsed: " << timeElapsed << ". [drawNoInputAnimationsV3()]\n";
        
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
//    std::cout << "End of anim request. \n";
}

void SceneController::drawWOInput(SceneRequest* request) {
//     std::cout << "At drawWOInput" << ". [drawWOInput()]\n";
    if (sceneTimer->isPaused()) {
        sceneTimer->unpause();
    }
    
    int origFrameCount = mainController->getFrameCount();
    float gStartTime = sceneTimer->getTicks();
    float startTime;
    float timeDuration = request->getTimeDuration();
    
    if (timeDuration <= -1) {
        timeDuration = std::numeric_limits<float>::infinity();
    }
    
    // neither handleinput or update are called. Truly a still scene.
    while ((sceneTimer->getTicks() - gStartTime <= timeDuration) and !mainController->getEndScene()) {
        startTime = sceneTimer->getTicks();
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        
        if (request->hasText()) {
            drawWithTexts(request->getTextLs(), request->getTextPosnLs());
        } else {
            drawWithText(" ", Posn(200, 170));
        }
        
        update();

        float endTime = sceneTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        mainController->frameCountAdd(1);
    }

    if (!sceneTimer->isPaused()) {
        sceneTimer->pause();
    }
    mainController->setEndScene(false);
    mainController->setFrameCount(origFrameCount);
    request->setTimeDuration(0);
}

void SceneController::drawFadeOutSprites(SceneRequest* request) {
    // SceneRequest(enum SCENE scene, std::deque<Sprite*> sprites, float time)
//    std::cout << "At drawFadeOutSprites(). [sceneController]\n";
    std::deque<Sprite*> spritesToRecur = request->getSpritesToFadeOut();

    if (sceneTimer->isPaused()) {
        sceneTimer->unpause();
    }
    
    float gStartTime = sceneTimer->getTicks();
    float startTime;
    float timeDuration = request->getTimeDuration();
    // neither handleinput or update are called. Truly a still scene.
    while ((sceneTimer->getTicks() - gStartTime <= timeDuration) and !mainController->getEndScene()) {
        startTime = sceneTimer->getTicks();
        // recur thru all sprites
        for (Sprite* spritePtr : spritesToRecur) {
            SDL_Surface* srfcToDraw;
            
            // get correct surface
            if (spritePtr->getStateDir() == LEFT) {
                srfcToDraw = spritePtr->getSheet(spritePtr->getState())->getSrfcL();
            } else {
                srfcToDraw = spritePtr->getSheet(spritePtr->getState())->getSrfcR();
            }
           
            SDL_SetSurfaceAlphaMod(srfcToDraw, (1 - ((sceneTimer->getTicks() - gStartTime) / timeDuration)) * 255.00);
        }

        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    mainController->setEndScene(true);
                    break;
            }
        }
        drawWithText(" ", Posn(200, 170));
        update();
        
        float endTime = sceneTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
    
    for (Sprite* spritePtr : spritesToRecur) {
        SDL_Surface* srfcToDraw;
        if (spritePtr->getStateDir() == LEFT) {
            srfcToDraw = spritePtr->getSheet(spritePtr->getState())->getSrfcL();
        } else {
            srfcToDraw = spritePtr->getSheet(spritePtr->getState())->getSrfcR();
        }
        SDL_SetSurfaceAlphaMod(srfcToDraw, 0);
    }
    
    if (!sceneTimer->isPaused()) {
        sceneTimer->pause();
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}
