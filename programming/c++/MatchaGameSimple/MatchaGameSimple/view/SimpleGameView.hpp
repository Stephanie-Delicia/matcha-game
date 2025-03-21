#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include "SimpleController.hpp"

// Class definition for a simple game view. View only displays one background for entire game.

class SimpleGameView {
    public:
        SimpleGameView();
        ~SimpleGameView();
    
        void openGame(); // opens SDL game window. uses controller to interpret player inputs.
    
    private:
        SimpleController;                // Simple controller for only walking a char
        SDL_Event events;                // player events
        SDL_Window* window;              // SDL game window
        SDL_Renderer* renderer;          // renderer
        SDL_Surface* background_surface; // background for game window
        bool exitGame;                   // bool for if user exits game window
};
