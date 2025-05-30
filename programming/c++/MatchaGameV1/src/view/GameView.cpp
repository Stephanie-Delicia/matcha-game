/*
    A base class for a game view.
 */
#include <string>
#include <iostream>
#include <SDL3/SDL.h>
#include "GameView.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

GameView::GameView() {
}

void GameView::initSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    createRenderer();
    TTF_Init();
    setFont();
}

void GameView::quitSDL() {
    SDL_Quit();
}

void GameView::draw(ScreenModel* activeScreen) {
    clearRender(); // Clear the renderer
    drawBGSrfc(activeScreen);
    drawMainSrfc(activeScreen);
    presentRender();
}

void GameView::drawSprite(Sprite *sprite) {
    // draws on main surface
    sprite->draw(mainSrfc);
}

void GameView::drawMainSrfc(ScreenModel* activeScreen) {
    SDL_Surface* mainSrfc = activeScreen->returnMSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, mainSrfc);
    SDL_FRect backgroundDest = {0, 0, activeScreen->getWidth(), activeScreen->getHeight()};
    SDL_RenderTexture(renderer, text, NULL, &backgroundDest);
    SDL_DestroySurface(mainSrfc);
    SDL_DestroyTexture(text);
}

void GameView::drawBGSrfc(ScreenModel* activeScreen) {
    SDL_Surface* bgSrfc = activeScreen->returnBGSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, bgSrfc);
    SDL_FRect backgroundDest = {0, 0, activeScreen->getWidth(), activeScreen->getHeight()};
    SDL_RenderTexture(renderer, text, NULL, &backgroundDest);
    SDL_DestroySurface(bgSrfc);
    SDL_DestroyTexture(text);
}

void GameView::drawWithFPS(ScreenModel* activeScreen, std::string fpsText) {
    clearRender(); // Clear the renderer
    drawBGSrfc(activeScreen);
    drawMainSrfc(activeScreen);
    
    if (genevaFont == NULL) {
        fprintf(stderr, "TTF_OpenFont failed! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_Surface* textSrfc = TTF_RenderText_Blended(genevaFont, fpsText.c_str(), fpsText.size(), fontColor);
    if (textSrfc == NULL) {
        fprintf(stderr, "TTF_RenderText_Solid failed! SDL_Error: %s\n", SDL_GetError());
    }
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSrfc);
    if (textTexture == NULL) {
        fprintf(stderr, "SDL_CreateTextureFromSurface failed! SDL_Error: %s\n", SDL_GetError());
    }
    bool success = SDL_RenderTexture(renderer, textTexture, NULL, &destFPSRect);
    if (success == 0) {
        fprintf(stderr, "SDL_RenderTexture failed! SDL_Error: %s\n", SDL_GetError());
    }
    presentRender();
    SDL_DestroySurface(textSrfc);
    SDL_DestroyTexture(textTexture);
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
    // 1 = opengl, best renderer thus far, 59 fps
    renderer = SDL_CreateRenderer(window, SDL_GetRenderDriver(1));
}

void GameView::presentRender() {
    SDL_RenderPresent(renderer);
}

void GameView::clearRender() {
    SDL_RenderClear(renderer);
}

void GameView::setFont() {
    genevaFont = TTF_OpenFont("/System/Library/Fonts/Geneva.ttf", 15);
}
