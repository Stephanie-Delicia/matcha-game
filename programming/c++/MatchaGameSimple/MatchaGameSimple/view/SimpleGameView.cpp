// Class for a simple game view.

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include "SimpleGameView.hpp"
#include "global_vars.hpp"

SimpleGameView::SimpleGameView() {
    // window pointer
    window = SDL_CreateWindow(GAME_TITLE,         // window title
                              SCREEN_WIDTH,       // in pixels
                              SCREEN_HEIGHT,      // in pixels
                              SDL_WINDOW_OPENGL); // on macOS
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
    
    // renderer pointer
    renderer = SDL_CreateRenderer(window, NULL);

    // surface pointer for basic background
    background_surface = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/backgrounds/calm_background.png");
    if (background_surface == NULL) {
            printf("Error with loading surface: %s\n", SDL_GetError());
        }
    
    // bool for if user exits game window
    exitGame = false;
}

SimpleGameView::~SimpleGameView() {
    SDL_DestroySurface(background_surface);
    SDL_DestroyWindow(window);
}

void SimpleGameView::openGame() {
    // texture pointer
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background_surface);
    SDL_FRect backgroundDest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; // { x, y, w, h }
    SDL_RenderTexture(renderer, backgroundTexture, NULL, &backgroundDest);
    SDL_RenderPresent(renderer);
    
    // for opening window
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3
    
    while (!exitGame) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                exitGame = true;
            }
        }

        // Rendering an image of my choosing
        // Do game logic, present a frame, etc.
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
}
