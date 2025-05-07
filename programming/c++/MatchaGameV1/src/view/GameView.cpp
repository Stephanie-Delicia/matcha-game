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
    std::cout << "Draw call. [View]" <<  "\n";
    drawBGSrfc(activeScreen);
    std::cout << "Draw background. [View]" <<  "\n";
    drawMainSrfc(activeScreen);
    std::cout << "Draw main. [View]" <<  "\n";
    render();
    std::cout << "Render call. [View]" <<  "\n";
    clearRender();
}

void GameView::drawSprite(Sprite *sprite) {
    // draws on main surface
    sprite->draw(mainSrfc); // draw this sprite on the window
}

void GameView::drawMainSrfc(ScreenModel* activeScreen) {
    SDL_Surface mainSrfc = activeScreen->returnMSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, &mainSrfc);
    SDL_RenderTexture(renderer, text, NULL, NULL);
}

void GameView::drawBGSrfc(ScreenModel* activeScreen) {
    
    SDL_Surface bgSrfc = activeScreen->returnBGSurface();
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, &bgSrfc);
    SDL_RenderTexture(renderer, text, NULL, NULL);
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

void GameView::render() {
    SDL_RenderPresent(renderer);
}

void GameView::clearRender() {
    SDL_RenderClear(renderer);
}
