/*
    A controller that extents the GameController class. Has added functionality for drawing scenes within the game, such as still scenes in which no user input is interpreted and scene transitions such as a fade to
    black.
 */
#include "SceneController.hpp"
#include "Timer.hpp"
#include "NAME.h"
#include "REQUEST.h"

void SceneController::drawStillScene(SceneRequest* request) {
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - startTime <= timeDuration) and !exitGame) {
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    exitGame = true;
                    break;
            }
        }
        drawWithText("Collect 20 boxes to win, bish!", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        countedFrames++;
    }
    exitGame = false;
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
        std::cout << "Sucess getting the alpha! [SceneController::drawFadeToBlack()]\n";
    }
    // make transparent
    if (alpha == 0) {
        std::cout << "The rectangle was already fully transparent. [SceneController::drawFadeToBlack()]\n";
    } else {
        bool success2 = SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), 0);
        std::cout << "Making the rectangle fully transparent. [SceneController::drawFadeToBlack()]\n";
    }
    // So, we're going to add that ish to the main screen's queues for drawing
    // Just the main queue! No updates needed.
    // So, we ensure its in the main queue, THEN, we alter the transparency.
    Sprite* blackScreenPtr = nameSpriteMap->getSprite(BLACK_SCREEN);
    bool inQueue = getModel()->getActiveScreen()->onScreen(blackScreenPtr);
    
    if (!inQueue) {
        getModel()->getActiveScreen()->addToMain(blackScreenPtr);
    }

    // Let's do like maybe 2 seconds for the fade
    // then we keep the screen on for the time duration.
    // when that's done, we have to have an immediate nav call, then a drawFadeOutOfBlack() call in the main controller queue.
    // that will have a set time like 2 seconds two, maybe.
    
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    float timeStep = timeDuration / 255.00;
    int alphaStep = 1;
    // neither handleinput or update are called. Truly a still scene.
    while ((fpsTimer->getTicks() - startTime <= timeDuration) and !exitGame) {
        SDL_SetSurfaceAlphaMod(blackScreenSheet->getSrfcL(), ((fpsTimer->getTicks() - startTime)/timeDuration) * 255.00);
        // game step
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    mainController->endGame();
                    exitGame = true;
                    break;
            }
        }
        drawWithText("Collect 20 boxes to win, bish!", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        gameDelay(timeElapsed); // TODO: I dont think this is running properly?
        countedFrames++;
    }
    exitGame = false;
    request->setTimeDuration(0);
    
    // DO NOT remove scree from screen queue. Need to call drawFadeOutOfBlack() to do this.
}

void SceneController::drawFadeOutOfBlack(SceneRequest* request) {
    
}

bool SceneController::hasRequests() {
    return (sceneRequests.size() > 0);
}

void SceneController::fulfillRequests() {
    std::cout << "[SceneController, fulfillRequests]\n";
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
    std::cout << "Added req ptr: " << req << ", [SceneController].\n";
    sceneRequests.push_front(req);
}

/*
 FOR TESTING:
 //    std::cout << "[SceneController, drawStillScene]\n";
 //    std::cout << "fpsTimer ptr: " << fpsTimer << " [SceneController, drawStillScene]\n";
 
 //    std::cout << "startTime: " << startTime << " [SceneController, drawStillScene]\n";
 //    std::cout << "timeDuration: " << timeDuration << " [SceneController, drawStillScene]\n";
 //    std::cout << "fpsTimer.getTicks(): " << fpsTimer->getTicks() << " [SceneController, drawStillScene]\n";
 
 //        std::cout << "startTime: " << startTime << " [SceneController, drawStillScene]\n";
 //        std::cout << "fpsTimer.getTicks(): " << fpsTimer->getTicks() << " [SceneController, drawStillScene]\n";
 //        std::cout << "fpsTimer.getTicks() - startTime >= timeDuration: " << (fpsTimer->getTicks() - startTime >= timeDuration) << " [SceneController, drawStillScene]\n";
 //        std::cout << "Time loop for [SceneController, drawStillScene].\n";
 
 //    std::cout << "Finished scene request. [drawStillScene]\n";
     // fpsTimer->stop();
 
 //    delete req;
 //    req = nullptr;
 */
