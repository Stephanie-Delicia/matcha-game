/*
 A concrete class that handles the states of a button that redirects the player to a different screen.
 After instantiation, the navigator and screen to navigate to MUST BE SET.
 */
#pragma once
#include "Posn.hpp"
#include <SDL3/SDL.h>
#include "Sprite.hpp"
#include "SpriteState.hpp"
#include "TranslateCommand.hpp"
#include "ScreenNavigator.hpp"
#include "ScreenModel.hpp"
#include "IdleCommand.hpp"

class NavButtonState : public SpriteState {
public:
    void update(Sprite* sprite);
    void draw(Sprite* sprite, SDL_Surface *windowSrfc);
    void handleInput(Sprite* sprite, const SDL_Event &input);

    // this sprite won't undergo any sort of transformation, so no command needed to handle updates
    void setScreenNav(ScreenNavigator* nav) { screenNav = nav; } ;
    void setScreenToNavTo(ScreenModel* screen) { screenToNavTo = screen; } ;
    
protected:
    IdleCommand idleC = IdleCommand();
    ScreenNavigator* screenNav;
    ScreenModel* screenToNavTo;
};
