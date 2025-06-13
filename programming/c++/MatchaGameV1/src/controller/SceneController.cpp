//
//  SceneController.cpp
//  MatchaGameV1
//
//  Created by Stephanie Martinez on 6/7/25.
//

#include "SceneController.hpp"
#include "Timer.hpp"

void SceneController::drawStillScene(SceneRequest* request) {
    // TODO: incorporate the timer...
    std::cout << "[SceneController, drawStillScene]\n";
    std::cout << "fpsTimer ptr: " << fpsTimer << " [SceneController, drawStillScene]\n";
    float startTime = fpsTimer->getTicks();
    float timeDuration = request->getTimeDuration();
    
    std::cout << "startTime: " << startTime << " [SceneController, drawStillScene]\n";
    std::cout << "timeDuration: " << timeDuration << " [SceneController, drawStillScene]\n";
    std::cout << "fpsTimer.getTicks(): " << fpsTimer->getTicks() << " [SceneController, drawStillScene]\n";

    // neither handleinput or update are called. Truly a still scene.
    while (fpsTimer->getTicks() - startTime <= timeDuration) {
        std::cout << "startTime: " << startTime << " [SceneController, drawStillScene]\n";
        std::cout << "fpsTimer.getTicks(): " << fpsTimer->getTicks() << " [SceneController, drawStillScene]\n";
        std::cout << "fpsTimer.getTicks() - startTime >= timeDuration: " << (fpsTimer->getTicks() - startTime >= timeDuration) << " [SceneController, drawStillScene]\n";
        std::cout << "Time loop for [SceneController, drawStillScene].\n";
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        drawWithText("Collect 20 boxes to win, bish!", Posn(200, 170));
        
        float endTime = fpsTimer->getTicks();
        float timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        countedFrames++;
    }
    std::cout << "Finished scene request. [drawStillScene]\n";
    // fpsTimer->stop();
    request->setTimeDuration(0);
}

bool SceneController::hasRequests() {
    return (sceneRequests.size() > 0);
}

void SceneController::fulfillRequests() {
    std::cout << "[SceneController, fulfillRequests]\n";
    std::deque<SceneRequest*> reqsToDelete;
    for (SceneRequest* req : sceneRequests) {
        // fulfill, then delete
        // TODO: do the switch cases for scene types
        drawStillScene(req);
        reqsToDelete.push_front(req);
    }
    
    // delete
    for (SceneRequest* req : reqsToDelete) {
        removeRequest(req);
    }
}

void SceneController::removeRequest(SceneRequest* req) {
    auto find_iterator = std::find(sceneRequests.begin(), sceneRequests.end(), req);
    if (find_iterator != sceneRequests.end()) {
        sceneRequests.erase(find_iterator);
    }
    // requests, when created, are dynamically allocated. Make sure to delete and then get rid of the
    // dangling pointer.
    // UPDATE: the deletion will occur in the main controller for now instead
//    delete req;
//    req = nullptr;
}

void SceneController::addRequest(SceneRequest* req) {
    std::cout << "Added req ptr: " << req << ", [SceneController].\n";
    sceneRequests.push_front(req);
}
