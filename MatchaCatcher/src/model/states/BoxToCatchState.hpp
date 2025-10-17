/*
 A concrete class that handles the states of a sprite that is falling and meant to be catched.
 */
#pragma once
#include "Posn.hpp"
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "TranslateCommand.hpp"
#include "GameController.hpp"

class BoxToCatchState : public SpriteState {
public:
    BoxToCatchState() {};
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);
    void setCommandTimers(Timer* timer) {transC.setTimer(timer);};
    void setGameController(GameController* controller) { gameController = controller; } ;
    
private:
    // command
    TranslateCommand transC = TranslateCommand();
    // controller for obtaining model info
    GameController* gameController; // to send scene requests to if needed.
};
