#pragma once
#include <string>
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "ScreenModel.hpp"

/*
    A base class for a game view.
 */

class GameView {
public:
    GameView();
    void initSDL();
    void quitSDL();
    
    // drawing and rendering
    void render();
    void clearRender();
    void drawSprite(Sprite* sprite);
    void draw(ScreenModel* activeScreen);
    void drawBGSrfc(ScreenModel* activeScreen);
    void drawMainSrfc(ScreenModel* activeScreen);
    
    // getters
    SDL_Event     getEvents();
    SDL_Window*   getWindow();
    SDL_Surface*  getBGSrfc(); // background = BG
    SDL_Surface*  getMainSrfc();
    SDL_Renderer* getRenderer();
    
    // create
    void createRenderer();
    void createBGSrfc(ScreenModel activeScreen);
    void createMainSrfc(ScreenModel activeScreen);
    void createWindow(std::string name, int w, int h);
    
private:
    SDL_Event     events;   // player events
    SDL_Window*   window;   // SDL game window
    SDL_Surface*  bgSrfc;   // background for game window
    SDL_Surface*  mainSrfc; // a temporary surface
    SDL_Renderer* renderer; // renderer
};
