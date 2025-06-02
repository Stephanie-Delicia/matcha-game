/*
    A base class for a game view.
 */
#pragma once
#include <vector>
#include "Posn.hpp"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Sprite.hpp"
#include "ScreenModel.hpp"

class GameView {
public:
    GameView();
    void initSDL();
    void quitSDL();
    
    // drawing and rendering
    void clearRender();
    void presentRender();
    void drawSprite(Sprite* sprite);
    void draw(ScreenModel* activeScreen);
    void drawWithText(ScreenModel* activeScreen, std::string text, Posn posn); // for a single text
    void drawWithTexts(ScreenModel* activeScreen, std::vector<std::string> textLs, std::vector<Posn> posnLs); // for multiple texts
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
    
    // for text
    void setFont();
    SDL_Color fontColor = {0, 0, 0, 255};
    TTF_Font* genevaFont;
};
