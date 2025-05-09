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
    clearRender(); // Clear the renderer
    drawBGSrfc(activeScreen);
    drawMainSrfc(activeScreen);
    presentRender();
}

void GameView::testDraw(ScreenModel* activeScreen, SDL_Texture texture) {
    clearRender(); // Clear the renderer
    drawBGSrfc(activeScreen);
    drawMainSrfc(activeScreen);
    SDL_FRect dsrect = {static_cast<float>(texture.w), static_cast<float>(texture.h), 0, 0};
    SDL_RenderTexture(renderer, &texture, NULL, &dsrect);
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
    renderer = SDL_CreateRenderer(window, SDL_GetRenderDriver(1));
    //
    // 1 = opengl, best renderer thus far, 59 fps
    // TODO: FOR SOME READON< WHEN I USE THE MOUSE, THE THING FRIGGIN SPEEDS UP WINNIE LOL
    std::cout << "renderers: " << SDL_GetRenderDriver(1) << "\n";
}

void GameView::presentRender() {
    SDL_RenderPresent(renderer);
}

void GameView::clearRender() {
    SDL_RenderClear(renderer);
}
