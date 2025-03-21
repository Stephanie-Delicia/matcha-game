#pragma once

#include <SDL3/SDL.h>
#include "SimpleGameModel.hpp"
#include "SimpleGameView.hpp"
// Class definition for a simple controller used for walking a char.

class SimpleController {
    public:
        SimpleController(SimpleGameModel m, SimpleGameView v);
        ~SimpleController();
    
        void openGame();                 // opens SDL game window. uses controller to interpret player inputs.
        void charMove(SDL_Event events); // Interpret user input for moving a char. (Also determine if the input makes sense)
    
    private:
        SimpleGameModel model;       // Simple model
        SimpleGameView view;         // Simple controller for only walking a char
        bool exitGame;               // bool for if user exits game window
};
