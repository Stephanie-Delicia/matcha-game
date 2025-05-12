/*
 Represents a game controller which: starts a game and determines which sprites of the model are updated and drawn.
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
    float delay;
    float spriteDelay;
    
    view->initSDL(); // initialize SDL from view

    fpsTimer.start(); // count fps
    
    // loop for each game step
    while (!exitGame) {
        startTime = fpsTimer.getTicks();
        avgFPS = measureFPS(); // Set text to be rendered
        
        SDL_Event event; // get events
        while( SDL_PollEvent(&event) )
        {
            handleInput(event); // events are passed on to sprites. controller chooses which.

            switch( event.type ) {
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        update();      // updates occur to sprites chosen by the controller.
        drawWithFPS(); // drawing is passed to the view
        
        // adjust for fps
        endTime = fpsTimer.getTicks();
        timeElapsed = endTime - startTime;
        delay = 0.0;
        spriteDelay = 0.0;
        if ( (1000 / fpsGoal) > timeElapsed )
        {   // stabilize frame rate by bridging the difference
            delay = (1000 / fpsGoal) - timeElapsed;
            spriteDelay = (1000 / 25) - timeElapsed - delay;
            SDL_Delay(delay);
            updateSpriteTime(timeElapsed, spriteDelay);
        }
        ++countedFrames;
    }

    // Clean up
    view->quitSDL();
}

void GameController::update() {
    // controller calls on the model for this
    model->getMainPlayer()->update();
}

void GameController::updateSpriteTime(float timeElapsed, float timeDelay) {
    Sprite* mainPlayer = model->getMainPlayer();
    float currFrameTime = mainPlayer->getCurrFrameTime();
    if (currFrameTime <= 0.0) {
        mainPlayer->setCurrFrameTime(timeDelay);
    } else {
        mainPlayer->setCurrFrameTime(currFrameTime - timeElapsed);
    }
}

void GameController::draw() {
    // the active screen contains (1) the background to draw on first and (2) extra stuff like the main player sprite
    // view draws based on the model's active screen
    view->draw(model->getActiveScreen());
}

void GameController::drawWithFPS() {
    view->drawWithFPS(model->getActiveScreen(), fpsText);
}

void GameController::handleInput(SDL_Event const &event) {
    // using the model, the game controller will choose which sprites have to interpret events
    // rather than making the model select who gets this call, we'll leave it here with the controller
    model->getMainPlayer()->handleInput(event);
}

float GameController::measureFPS() {
    float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
    if( avgFPS > 10000 ) {
        avgFPS = 0; // to correct the initial high fps from starting
    }
    fpsText = "Average FPS: " + std::to_string((int) std::round(avgFPS));
    return avgFPS;
}

/*
 FOR DEBUGGING:
 // std::cout << "Started a game step. [controller]\n";
 // TODO: Look into properly giving Sprite classes abstractions for states
 // TODO: Draft and determine the gameplay you want to implement
 // TODO: Read on learncpp. Look into memory leaks, better practices with pointers.
 // TODO: Make code private where it should be.
 // TODO: make function params const where it should be.
 // TODO: Have either the main or active screen provide a list of sprites to update
 // TODO: Destroy window when exiting game.
 Texturewise:
 - Drink pngs
 - Maybe running animation
 - A drinking animation
 - Thumbs up animation
 - Revolving animation
 // std::cout << timeText << "\n";
 // std::cout << "delay: " << delay << "\n";
 // std::cout << "spriteDelay: " << spriteDelay << "\n";
 */
