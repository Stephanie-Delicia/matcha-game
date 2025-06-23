/*
 A concrete class that handles the states of a character sprite (one that can be moved with keyboard arrows).
 */
#pragma once
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"
#include "GameController.hpp"
#include "JumpingCommand.hpp"

class CharacterState : public SpriteState {
public:
    CharacterState(float width, float height) {
        screenWidth = width;
        screenHeight = height;
        walkingC.setScreenWidth(screenWidth);
    };
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);
    void setWidth(float width)   { screenWidth  = width; };
    void setJumpingCommand() {
        jumpingC.setTimer(gameController->getTimer());        
    };
    void setHeight(float height) { screenHeight = height; };
    void setGameController(GameController* controller) { gameController = controller; } ;
    
private:
    // commands
    float screenWidth;
    float screenHeight;
    IdleCommand idleC = IdleCommand();
    WalkingCommand walkingC = WalkingCommand();
    JumpingCommand jumpingC = JumpingCommand();
    
    // controller for obtaining model info
    GameController* gameController; // to send scene requests to if needed.
};
