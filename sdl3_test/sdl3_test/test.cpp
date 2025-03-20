// Example program:
// Using SDL3 to create an application window

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>

int main(int argc, char* argv[]) {

    // Declare pointer for window
    int SCREEN_WIDTH = 640;
    int SCREEN_HEIGHT = 360;
    SDL_Window *window;
    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        360,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );
    
    // Declare renderer
    SDL_Renderer* renderer;
    renderer = SDL_CreateRenderer(window, NULL);
    

    // Declare surface and texture for background
    SDL_Surface* backgroundImageSrf = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/textures/backgrounds/calm_background.png");
    if (backgroundImageSrf == NULL) {
            printf("Error with loading surface: %s\n", SDL_GetError());
        }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundImageSrf);

    SDL_FRect backgroundDest = {0, 0, 640, 360}; // { x, y, w, h }

    SDL_RenderTexture(renderer, backgroundTexture, NULL, &backgroundDest);
    SDL_RenderPresent(renderer);
    
    
    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL3
    bool done = false;                     // for when the program is done

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
            }
        }

        // Rendering an image of my choosing
        
        // Do game logic, present a frame, etc.
    }

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    SDL_Quit();
    return 0;
}
