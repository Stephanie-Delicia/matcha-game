#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_pixels.h>
#include "SimpleGameView.hpp"
#include "global_vars.hpp"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include <iostream>
#include <cmath>

// Class for a simple game view.
// TODO:for some reason, the sprite position does change, but i cannot render them onto the screen!

SimpleGameView::SimpleGameView() {
    // window pointer
    window = SDL_CreateWindow(GAME_TITLE,         // window title
                              SCREEN_WIDTH,       // in pixels
                              SCREEN_HEIGHT,      // in pixels
                              SDL_WINDOW_OPENGL); // on macOS
    if (window == NULL) {
        // If the window could not be made
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
    
    // renderer pointer
    renderer = SDL_CreateRenderer(window, NULL);
    // std::cout << "\n ren. address in init(): "  << &renderer << " ";
    
    // surface pointer for basic background
    background_surface = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/backgrounds/calm_background.png");
    if (background_surface == NULL) {
            printf("Error with loading surface: %s\n", SDL_GetError());
        }
    
    // texture pointer
//    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background_surface);
//    SDL_FRect backgroundDest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; // { x, y, w, h }
//    SDL_RenderTexture(renderer, backgroundTexture, NULL, &backgroundDest);
//
//    SDL_RenderPresent(renderer);
//    SDL_RenderClear(renderer);
    // std::cout << "\n  #2: ren. address in init(): "  << &renderer << " ";
}

SimpleGameView::~SimpleGameView() {
    SDL_DestroySurface(background_surface);
    SDL_DestroyWindow(window);
}

void SimpleGameView::initializeSDL() {
    // initializing SDL3
    SDL_Init(SDL_INIT_VIDEO);
}

void SimpleGameView::destroyWindow() {
    // Close and destroy the window
    SDL_DestroyWindow(window);
}

void SimpleGameView::quitSDL() {
    // Clean up
    SDL_Quit();
}

void SimpleGameView::drawChar(Sprite* sprite) {
    // SDL_RenderTexture(renderer, backgroundTexture, NULL, &backgroundDest);
    // SDL_RenderPresent(renderer);
    // std::cout << "We get to here in view."; OLD:
//    SDL_Surface* winnie_surface = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/textures/chars/animations/winnie/idle.png");
//    SDL_Texture* char_text = SDL_CreateTextureFromSurface(renderer, winnie_surface);

    // Render the texture at a specific location
//    SDL_FRect destRect = {sprite.getXPosn(), sprite.getYPosn(), 54, 70}; // x, y, width, height
//    SDL_RenderTexture(renderer, char_text, NULL, &destRect);
//    SDL_RenderPresent(renderer);
//    SDL_RenderClear(renderer); // clears the renderer
    //std::cout << "\n sprite add in view draw function: " << sprite;
    //std::cout << "\n spriteSheet address in view draw function: " << sprite->getSpriteSheet() << "\n";
    // Get sheet
    // BLITZ TF OUT OF IT
    // just get the src rect from function
    SpriteSheet* sheetPtr = sprite->getSpriteSheet();
    SDL_Surface* sheetSrfc = sheetPtr->getSheetSrfc();    
    // ERROR HERE:
    std::cout << "\n currFrame in drawChar: " << sheetPtr->getCurrFrame();
    std::cout << "\n sprite location in drawChar: " << sprite->getXPosn() << ", " << sprite->getYPosn();
    SDL_Rect srcRect = sheetPtr->getCurrFrameRect();
    std::cout << "\n srcRect x: " << srcRect.x;
    std::cout << "\n srcRect y: " << srcRect.y;
    std::cout << "\n srcRect h: " << srcRect.h;
    std::cout << "\n srcRect w: " << srcRect.w;
    SDL_Rect destRect = {static_cast<int>(sprite->getXPosn()),
        static_cast<int>(sprite->getYPosn()),
        54,
        70};
    std::cout << "\n destRect x: " << destRect.x;
    std::cout << "\n destRect y: " << destRect.y;
    std::cout << "\n destRect h: " << destRect.h;
    std::cout << "\n destRect w: " << destRect.w;
    std::cout << "\n sheet frames total: " << sheetPtr->getNumFrames();
    int success = SDL_BlitSurface(sheetSrfc, &srcRect, background_surface, &destRect);
    if (success < 1) {
        fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
    }
    
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, background_surface);
    SDL_FRect backgroundDest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; // { x, y, w, h }
    SDL_RenderTexture(renderer, backgroundTexture, NULL, &backgroundDest);
    SDL_RenderPresent(renderer);
    // SDL_UpdateWindowSurface(window);
    
    
    //
    SDL_RenderClear(renderer);
}

SDL_Event SimpleGameView::getEvents() {
    return events;
}

SDL_Window* SimpleGameView::getWindow() {
    return window;
}

SDL_Renderer* SimpleGameView::getRenderer() {
    return renderer;
}

SDL_Surface* SimpleGameView::getBackgroundSrfc() {
    return background_surface;
}
