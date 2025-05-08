#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include "GameView.hpp"
#include <SDL3_image/SDL_image.h>

GameView::GameView() {
    
}

void GameView::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
}

void GameView::quitSDL() {
    SDL_Quit();
}

void GameView::draw(ScreenModel* activeScreen) {
    // Clear the screen
    SDL_RenderClear(renderer);
    drawBGSrfc(activeScreen);
    drawMainSrfc(activeScreen);
    
    presentRender();
}

void GameView::drawSprite(Sprite *sprite) {
    // draws on main surface
    sprite->draw(mainSrfc); // draw this sprite on the window
}

void GameView::drawMainSrfc(ScreenModel* activeScreen) {
    SDL_Surface* mainSrfc = activeScreen->returnMSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, mainSrfc);
    SDL_FRect backgroundDest = {0, 0, activeScreen->getWidth(), activeScreen->getHeight()};
    SDL_RenderTexture(renderer, text, NULL, &backgroundDest);
}

void GameView::drawBGSrfc(ScreenModel* activeScreen) {
    SDL_Surface* bgSrfc = activeScreen->returnBGSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, bgSrfc);
    SDL_FRect backgroundDest = {0, 0, activeScreen->getWidth(), activeScreen->getHeight()};
    SDL_RenderTexture(renderer, text, NULL, &backgroundDest);
}

SDL_Event GameView::getEvents() {
    return events;
}

SDL_Window* GameView::getWindow() {
    return window;
}

SDL_Surface* GameView::getBGSrfc() {
    return bgSrfc;
}

SDL_Renderer* GameView::getRenderer() {
    return renderer;
}

void GameView::createWindow(std::string name, int w, int h) {
    window = SDL_CreateWindow(name.c_str(), w, h, SDL_WINDOW_OPENGL); // on macOS
    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
    }
}

void GameView::createRenderer() {
    renderer = SDL_CreateRenderer(window, NULL);
}

void GameView::presentRender() {
    SDL_RenderPresent(renderer);
}

void GameView::clearRender() {
    SDL_RenderClear(renderer);
}

/*
 FOR TROUBLESHOOTING:
 
 // TEST, RENDER AN IDLE WINNIE DAMMIT
 //    SDL_Surface* testSurface = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/textures/background/pleasant_sky.png");
 //    SDL_Surface* winnieSrfc = IMG_Load("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/textures/chars/idle_left.png");
 //    SDL_Rect frameRect = {0, 0, 54, 70};
 //    SDL_Rect backgroundDest = {0, 180, 54, 70};
 //    bool success = SDL_BlitSurface(winnieSrfc, &frameRect, testSurface, &backgroundDest);
 //    std::cout << "IM GOING CRAZY: " << success << "\n";
 //    SDL_Texture* testTexture = SDL_CreateTextureFromSurface(renderer, testSurface);
 //    SDL_FRect bgDest = {0.0, 0.0, 640.0, 360.0};
 //    SDL_RenderTexture(renderer, testTexture, NULL, &bgDest);
 */
