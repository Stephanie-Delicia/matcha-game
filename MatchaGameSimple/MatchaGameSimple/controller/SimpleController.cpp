//
//  Represents a simple controller for the matcha game. Allows user to walk main char
//  around. Switched between main chars by presing the space bar.
//  You can only move a char left or right, within the screen bounds.

// Important note, when you return a parameter that is an object, you'll only return a COPY of that object.
// So, be sure that you always use methods that are from the class you want to mutate.

#include "SimpleController.hpp"
#include "SimpleGameView.hpp"
#include "SimpleGameModel.hpp"
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "Sprite.hpp"
#include <iostream>

SimpleController::SimpleController(SimpleGameModel& m, SimpleGameView& v) {
    // Pass by reference, we want to mutate the original model and view.
    // set given model and view
    model = &m; // access pointer
    view = &v;
//    std::cout << "\n numFrames in controller constructor: " << model->getSprite()->getSpriteSheet()->getNumFrames();
//    std::cout << "\n sprite add in controller constructor: " << model->getSprite();
//    std::cout << "\n spriteSheet add in controller constructor: " << model->getSprite()->getSpriteSheet();
    exitGame = false;
}

SimpleController::~SimpleController() {
    // TODO:
}

void SimpleController::openGame() {
    
    // initialize SDL from the view
    view->initializeSDL();
    
    while (!exitGame) {
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            updateCharDir(event); // set new Char DIRECTION
            switch(event.type)
            {
                case SDL_EVENT_QUIT:
                    
                    exitGame = true;
                    break;
            }
        }
        view->drawChar(model->getSprite());
    }

    // Close and destroy the window
    view->destroyWindow();

    // Clean up
    view->quitSDL();
}

void SimpleController::updateCharDir(SDL_Event const &event) {
    switch (event.type)
    {
        case SDL_EVENT_KEY_DOWN: {
            const bool *keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_UP] == 1)
            {
                model->updateCharDir(DIRECTION::UP);
            }
            else if (keys[SDL_SCANCODE_DOWN] == 1)
            {
                model->updateCharDir(DIRECTION::DOWN);
            }
            else if (keys[SDL_SCANCODE_LEFT] == 1)
            {
                model->updateCharDir(DIRECTION::LEFT);
                model->getSprite()->setIdleDir(DIRECTION::LEFT);
                updateCharPosn(1);
                model->getSprite()->updateSpreadSheetFrameNum();
            }
            else if (keys[SDL_SCANCODE_RIGHT] == 1)
            {
                model->updateCharDir(DIRECTION::RIGHT);
                model->getSprite()->setIdleDir(DIRECTION::RIGHT);
                updateCharPosn(2);
                model->getSprite()->updateSpreadSheetFrameNum();
//                std::cout << "Char x posn: " << model->getCharXPosn() << " ";
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            model->updateCharDir(DIRECTION::NONE);
            model->getSprite()->resetSpreadSheetFrameNum();
            break;
        }
    }
}

void SimpleController::updateCharPosn(double delta_time)
{
    model->updateCharPosn(delta_time);
}
