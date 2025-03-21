#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include "SimpleGameModel.hpp"
#include "SimpleGameView.hpp"

// Class definition for a simple controller used for walking a char.

class SimpleController {
    public:
        SimpleController();
        ~SimpleController();
    
        void charMove(SDL_Event events); // Interpret user input for moving a char. (Also determine if the input makes sense)
    
    private:
        SimpleGameModel;  // Simple controller for only walking a char
        SimpleGameView;   // Simple view
};
