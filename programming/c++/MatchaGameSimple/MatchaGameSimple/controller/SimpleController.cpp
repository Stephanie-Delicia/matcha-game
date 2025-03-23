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
    // std::cout << "\n before controller constr. ";
    view = &v;
    // std::cout << "\n view add: " << &view;
    // std::cout << "\n v add: " << &v;
    // std::cout << "\n after controller constr. ";
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
        // std::cout << "\n view addressn in controller: "  << &view << " ";
        view->drawChar(model->getSprite());
    }

    // Close and destroy the window
    view->destroyWindow();

    // Clean up
    view->quitSDL();
}

void SimpleController::updateCharDir(SDL_Event const &event) {
//    std::cout << "event.type: "  << event.type << " ";
//    std::cout << "SDL_EVENT_KEY_DOWN: "  << SDL_EVENT_KEY_DOWN << " ";
    switch (event.type)
    {
        case SDL_EVENT_KEY_DOWN: {
            const bool *keys = SDL_GetKeyboardState(nullptr);
//            std::cout << "keys[SDL_SCANCODE_RIGHT]: " << keys[SDL_SCANCODE_RIGHT] << " ";
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
                updateCharPosn(1);
            }
            else if (keys[SDL_SCANCODE_RIGHT] == 1)
            {
                model->updateCharDir(DIRECTION::RIGHT);
                updateCharPosn(1);
//                std::cout << "Char x posn: " << model.getCharXPosn() << " ";
//                std::cout << "Char y posn: " << model.getCharYPosn() << " ";
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            model->updateCharDir(DIRECTION::NONE);
            break;
        }
    }
}

void SimpleController::updateCharPosn(double delta_time)
{
    model->updateCharPosn(delta_time);
}
