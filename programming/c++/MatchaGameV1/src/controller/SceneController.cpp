//
//  SceneController.cpp
//  MatchaGameV1
//
//  Created by Stephanie Martinez on 6/7/25.
//

#include "SceneController.hpp"

void SceneController::drawStillScene(SceneRequest* request) {
    // TODO: incorporate the timer...
    float startTime = fpsTimer.getTicks();
    float timeDuration = request->getTimeDuration();

    // neither handleinput or update are called. Truly a still scene.
    while (fpsTimer.getTicks() - startTime >= timeDuration) {
        SDL_Event event;
        while( SDL_PollEvent(&event) )
        {
            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        draw();
    }
    request->setTimeDuration(0);
    removeRequest(request);
}

bool SceneController::hasRequests() {
    return (sceneRequests.size() > 0);
}

void SceneController::fulfillRequests() {
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
//    auto find_iterator = std::find(sceneRequests.begin(), sceneRequests.end(), req);
//    if (find_iterator != sceneRequests.end()) {
//        sceneRequests.erase(find_iterator);
//    }
}

void SceneController::addRequest(SceneRequest* req) {
    sceneRequests.push_front(req);
}
