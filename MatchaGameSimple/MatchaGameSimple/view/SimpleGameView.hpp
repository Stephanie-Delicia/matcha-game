#pragma once

#include <SDL3/SDL.h>
#include "Sprite.hpp"

// Class definition for a simple game view. View only displays one background for entire game.
// View has a model.

class SimpleGameView {
    public:
        SimpleGameView();
        ~SimpleGameView();
    
        void initializeSDL(); // initialized SDL3
        void destroyWindow();
        void quitSDL();
        void drawChar(Sprite* sprite);
        SDL_Event getEvents();
        SDL_Window* getWindow();
        SDL_Renderer* getRenderer();
        SDL_Surface* getBackgroundSrfc();
    
    private:
        SDL_Event events;                // player events
        SDL_Window* window;              // SDL game window
        SDL_Renderer* renderer;          // renderer
        SDL_Surface* background_surface; // background for game window
        SDL_Surface* temp_surface;
};
