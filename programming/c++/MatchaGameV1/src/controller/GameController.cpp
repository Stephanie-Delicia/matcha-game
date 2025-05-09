#include "Timer.hpp"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <iostream>
#include <string>
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"

// Represents a game controller which: starts a game and determines which sprites of the model are updated and drawn.

void GameController::startGame() {
    view->initSDL(); // initialize SDL from view

    // count fps
    fpsTimer.start();
    int fpsGoal = 60;
    
    while (!exitGame) {
        // Calculate and correct fps
        float startTime = fpsTimer.getTicks();
        float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
        if( avgFPS > 2000000 )
        { // to correct the initial high fps from starting
            avgFPS = 0;
        }
        
        // Set text to be rendered
        timeText = "Average FPS: ";
        timeText.append(std::to_string(avgFPS));
        std::cout << timeText << "\n";
        SDL_Event event; // get events
        
        while( SDL_PollEvent(&event) )
        {
            handleInput(event); // events are passed on to sprites. controller chooses which.

            switch( event.type ) {
                // we'll interpret events here in the controller too, but only for exiting the game
                case SDL_EVENT_QUIT:
                    exitGame = true;
                    break;
            }
        }
        update(); // similarly, updates occur to sprites chosen by the controller.
        float endTime = fpsTimer.getTicks();
        float timeElapsed = endTime - startTime;
        float delay = 0.0;
        if ( (1000 / fpsGoal) > timeElapsed )
        {
            delay = (1000 / fpsGoal) - timeElapsed; // stabilize frame rate by bridging the difference
            std::cout << "delay: " << delay << "\n";
            SDL_Delay(delay);
        }
        float spriteDelay = (1000 / 20) - (endTime - startTime) - delay;
        draw(); // Drawing is passed to the view

        ++countedFrames;
    }

    // Clean up
    view->quitSDL();
}

void GameController::update() {
    // controller calls on the model for this
    // TODO: I'll give the model its own update method to make this call more direct
    // The nav gets all set up, but the model doesn't. Update the model's main player! LOL
    model->getMainPlayer()->update();
}

void GameController::draw() {
    // view draws based on the model's active screen
    // the active screen contains (1) the background to draw on first and (2) extra stuff like the main player sprite
    // TODO: give the model a return function that returns WHAT should get drawn
    view->draw(model->getActiveScreen());
}

void GameController::handleInput(SDL_Event const &event) {
    // using the model, the game controller will choose which sprites have to interpret events
    // rather than making the model select who gets this call, we'll leave it here with the controller
    //TODO: I'll give the model its own method to make this call more direct
    model->getMainPlayer()->handleInput(event);
}

/*
 FOR DEBUGGING:
 
 // std::cout << "Started a game step. [controller]\n";
 // TODO; at 200 ms, you notice that quickly changing directions results in a brief idle animation.
 // not sure exactly how to solve that - wshould I decrease the delay time when I am changing directions?
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
 
 //    TTF_TextEngine* textEngine = TTF_CreateRendererTextEngine(view->getRenderer());
 //    TTF_Font* sansFont = TTF_OpenFont("Sans.ttf", 24);
 
 //        //this opens a font style and sets a size
 //        TTF_Text* text = TTF_CreateText(textEngine, sansFont, timeText.c_str(), timeText.size());
 //        TTF_DrawRendererText(text, 5.0, 5.0);
 //        SDL_RenderPresent(view->getRenderer());
 */

void GameController::measureFPS() {
}
