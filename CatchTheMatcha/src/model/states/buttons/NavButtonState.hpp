/*
 A concrete class that handles the states of a button that redirects the player to a different screen.
 After instantiation, the navigator and screen to navigate to MUST BE SET.
 */
#pragma once
#include "../SpriteState.hpp"

class NavButtonState : public SpriteState {
public:
    NavButtonState() {};
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);

    // this sprite won't undergo any sort of transformation, so no command needed to handle updates
    void setGameController(GameController* controller) { gameController = controller; } ;
    void setScreenToNavTo(ScreenModel* screen) { screenToNavTo = screen; } ;
    
protected:
    GameController* gameController; // to send scene requests to if needed.
    IdleCommand idleC = IdleCommand();
    ScreenModel* screenToNavTo;
    TranslateCommand transC = TranslateCommand();
};
