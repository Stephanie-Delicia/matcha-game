/*
    A controller that extents the GameController class. Has added functionality for drawing scenes within the game, such as still scenes in which no user input is interpreted and scene transitions such as a fade to
    black.
 */
#include "SceneController.hpp"
#include "Timer.hpp"
#include "NAME.h"
#include "REQUEST.h"
#include <limits>

void SceneController::drawStillScene(SceneRequest* request) {
    std::cout << "At drawStillScene" << ". [drawStillScene()]\n";
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    if (timeDuration <= -1) {
        timeDuration = std::numeric_limits<float>::infinity();
    }
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - startTime <= timeDuration) and !mainController->getEndScene()) {
        std::cout << "End scene bool: " << mainController->getEndScene() << ". [drawStillScene()]\n";
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
        
        drawWithText("Collect 5 boxes to win, bish!", Posn(200, 170));
        updateUI();

        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        mainController->frameCountAdd(1);
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

// TODO: I think I need to add a sprite name map to the function call
void SceneController::drawFadeToBlack(SceneRequest* request) {
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
    
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - startTime <= timeDuration) and !mainController->getEndScene()) {
        SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), ((fpsTimer->getTicks() - startTime)/timeDuration) * 255.00);
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
        drawWithText("Collect 5 boxes to win, bish!", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        mainController->frameCountAdd(1);
    }
    mainController->setEndScene(false);
    request->setTimeDuration(0);
}

void SceneController::removeBlackScreen() {
    NameSpriteMap* nameSpriteMap = getModel()->getNameSpriteMap();
    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = getModel()->getActiveScreen()->onScreen(blackScreenPtr);
    
    if (inQueue) {
        getModel()->getActiveScreen()->removeMain(blackScreenPtr);
    }
}

void SceneController::addBlackScreen(ScreenModel* screenToSetup) {
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
    
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - startTime <= timeDuration) and !mainController->getEndScene()) {
        SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), (1 - ((fpsTimer->getTicks() - startTime)/timeDuration)) * 255.00);
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
        drawWithText("Collect 5 boxes to win, bish!", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        mainController->gameDelay(timeElapsed);
        mainController->frameCountAdd(1);
    }
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
                
            case FADE: {
                drawFadeToBlack(req);
                break;
            }
                
            case UNFADE: {
                drawFadeOutOfBlack(req);
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
