/*
 A concrete class that handles the states of a button resets the game for the player, while on the gameplay screen. I think that the state should delegate to the controller, and the controller will have more
    specifics on what restarting entails.
 */
#pragma once
#include "../SpriteState.hpp"

class ExitButtonState : public SpriteState {
public:
    ExitButtonState() {};
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);

    // this sprite won't undergo any sort of transformation, so no command needed to handle updates
    void setGameController(GameController* controller) { gameController = controller; } ;
    
protected:
    GameController* gameController; // to send scene requests to if needed.
    IdleCommand idleC = IdleCommand();
    TranslateCommand transC = TranslateCommand();
};
