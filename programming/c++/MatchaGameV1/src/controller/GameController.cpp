/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Timer.hpp"
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"

void GameController::startGame() {
    float startTime;
    float endTime;
    float avgFPS;
    float timeElapsed;
    
    view->initSDL();
    fpsTimer.start();
    
    // game step loop
    while (!exitGame) {
        startTime = fpsTimer.getTicks();
        avgFPS = measureFPS();
        setFPSText(avgFPS);
        
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
        
        // adjust fps
        endTime = fpsTimer.getTicks();
        timeElapsed = endTime - startTime;
        gameDelay(timeElapsed);
        ++countedFrames;
    }

    // quit
    view->quitSDL();
}

void GameController::update() {
    getModel()->update();
}

void GameController::handleInput(SDL_Event const &event) {
    getModel()->handleInput(event);
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
    view->drawWithText(getModel()->getActiveScreen(), fpsText, Posn(100.00, 15.00));
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
    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
    if( avgFPS > 10000 ) {
        avgFPS = 0; // correct initial high fps
    }
    return avgFPS;
}

void GameController::setFPSText(int fps) {
    fpsText = "Average FPS: " + std::to_string((int) std::round(fps));
}
