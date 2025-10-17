/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Timer.hpp"
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"
#include "SceneController.hpp"
#include "SceneRequest.hpp"
#include "TimerRequest.hpp"
#include "NavRequest.hpp"
#include "../utils/enum/REQUEST.h"

void GameController::startGame() {
    float startTime;
    float endTime;
    float avgFPS;
    float timeElapsed;
    
    fpsTimer = new Timer();
    view->initSDL();
    fpsTimer->start();
    SDL_RaiseWindow(view->getWindow());
    // game step
    while (!exitGame) {
        // for measuring fps
        startTime = fpsTimer->getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);

        // get events and handle them, update sprites, and draw accordingly
        handleEvents();

        // for adjusting fps
        endTime = fpsTimer->getTicks();
        timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        ++countedFrames;
    }

    // quit the window
    view->quitSDL();
}

void GameController::update() {
    getModel()->update();
}

void GameController::updateUI() {
    getModel()->updateUI();
}

void GameController::handleInput(SDL_Event const &event) {
    getModel()->handleInput(event);
}

void GameController::handleMainSprite(const SDL_Event &event) {
    getModel()->handleMainSprite(event);
}

void GameController::handleWithoutMainSprite(const SDL_Event &event) {
    getModel()->handleWithoutMainSprite(event);
}

void GameController::handleInputForUI(SDL_Event const &event) {
    getModel()->handleInputForUI(event);
}

void GameController::handleEvents() {
    // Findings, I think SDL_PollEvent will literally only pick up on events when the user
    // does something, like move their mouse or press a key
    SDL_Event event;
    while( SDL_PollEvent(&event) )
    {
        handleInput(event);
        switch( event.type ) {
            case SDL_EVENT_QUIT:
                exitGame = true;
                break;
        }
    }
    update();
    drawWithFPS();
}

void GameController::draw() {
    // model's active screen contains the background to draw first and then other sprites on top
    view->draw(getModel()->getActiveScreen());
}

void GameController::drawWithText(std::string text, Posn posn) {
    // model's active screen contains the background to draw first and then other sprites on top
     view->drawWithText(getModel()->getActiveScreen(), text, posn);
}

void GameController::drawWithTexts(std::vector<std::string> textLs, std::vector<Posn> posnLs) {
    // model's active screen contains the background to draw first and then other sprites on top
     view->drawWithTexts(getModel()->getActiveScreen(), textLs, posnLs);
}

void GameController::drawWithFPS() {
    view->drawWithText(getModel()->getActiveScreen(), fpsText, Posn(10, 15.00));
}

void GameController::gameDelay(float timeElapsed) {
    // stabilize frame rate by bridging the difference
    if ( (1000 / fpsGoal) > timeElapsed )
    {
        float delay = (1000 / fpsGoal) - timeElapsed;
        SDL_Delay(delay);
        getModel()->delayFrameTimes(delay, timeElapsed); // for active sprites
    }
}

void GameController::delay(float time) {
    SDL_Delay(time);
}

float GameController::measureFPS() {
    float avgFPS = countedFrames / ( fpsTimer->getTicks() / 1000.f );
    if( avgFPS > 10000 ) {
        avgFPS = 0; // correct initial high fps
    }
    return avgFPS;
}

void GameController::setFPSText(int fps) {
    fpsText = "Average FPS: " + std::to_string((int) std::round(fps));
}

void GameController::setSceneController() {
    // Scene controller need not be manually assigned, a whole new one is created w/ each main game controller.
    sceneController = new SceneController(getModel(), view, this);
    // The scene controller uses the same timer for performing scenes
    sceneController->setTimer(fpsTimer);
    sceneController->getSceneTimer()->start();
}

void GameController::addRequest(Request* request) {
    requests.push_front(request);
}

void GameController::removeRequest(Request* request) {
    auto find_iterator = std::find(requests.begin(), requests.end(), request);
    if (find_iterator != requests.end()) {
        requests.erase(find_iterator);
    }
    // requests, when created, are dynamically allocated. Make sure to delete and then get rid of the
    // dangling pointer.
    delete request;
    request = nullptr;
}

void GameController::handleRequests() {
    std::deque<Request*> reqsToDelete;
    // recur thru requests in the event queue
    for (Request* req : requests) {
//        std::cout << "req type." << req->getReqType() << ". [GameController, handleRequests()]\n";
        // add to list of requests to de;ete
        switch (req->getReqType()) {
            case SCENE: {
                // for lower hiearchy relationships, we can luckily use dynamic_cast! Yay!
                // WARNING: I hope this isnt cause for a memory leak. Reqs, when created, are
                // dynamically allocated, so I wonder if dynamic_cast does the same for such an object.
                SceneRequest* sceneReq = dynamic_cast<SceneRequest*>(req);
                sceneController->addRequest(sceneReq);
//                std::cout << "SceneReq time duration: " << sceneReq->getTimeDuration() << " . [GameController::handleRequests()]\n";
                // Fulfill the draw request, then delete it HERE
                sceneController->fulfillRequests();
                reqsToDelete.push_front(req);
                break;
            }
            case NAVIGATE: {
                NavRequest* navReq = dynamic_cast<NavRequest*>(req);
//                std::cout << "Set new main screen to: " << navReq->getScreenModel()->screenType() << " . [GameController::handleRequests()]\n";
                screenNav->setMainScreen(navReq->getScreenModel());
                reqsToDelete.push_front(req);
                break;
            }
            case TIMER: {
                TimerRequest* timerReq = dynamic_cast<TimerRequest*>(req);
//                std::cout << "Handling a timer request. [GameController::handleRequests()]\n";
                if (timerReq->getPause()) {
                    gameplayTimer->pause();
                } else {
                    gameplayTimer->unpause();
                }
                reqsToDelete.push_front(req);
                break;
            }
            default: {
                // just delete it, otherwise, a weird unaccounted request type stays there forever!!
                reqsToDelete.push_front(req);
                break;
            }
        }
    }
    
    // delete
    for (Request* req : reqsToDelete) {
        removeRequest(req);
    }
}



