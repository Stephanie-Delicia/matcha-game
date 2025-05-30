/*
    Represents a game controller which: starts a game and calls on the game model and view to process updates.
 */

/*
 FOR DEBUGGING:
 // std::cout << "Started a game step. [controller]\n";
 // TODO: Look into properly giving Sprite classes abstractions for states
 // TODO: Draft and determine the gameplay you want to implement
 // TODO: Read on learncpp. Look into memory leaks, better practices with pointers.
 // TODO: Make code private where it should be.
 // TODO: make function params const where it should be.
 Texturewise:
 - Drink pngs
 - Maybe running animation
 - A drinking animation
 - Thumbs up animation
 - Revolving animation
 */
#include <cmath>
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
    model->update();
}

void GameController::handleInput(SDL_Event const &event) {
    model->handleInput(event);
}

void GameController::draw() {
    // model's active screen contains the background to draw first and then other sprites on top
    view->draw(model->getActiveScreen());
}

void GameController::drawWithFPS() {
    view->drawWithFPS(model->getActiveScreen(), fpsText);
}

void GameController::gameDelay(float timeElapsed) {
    // stabilize frame rate by bridging the difference
    if ( (1000 / fpsGoal) > timeElapsed )
    {
        float delay = (1000 / fpsGoal) - timeElapsed;
        SDL_Delay(delay);
        model->delayFrameTimes(delay, timeElapsed); // for active sprites
    }
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
