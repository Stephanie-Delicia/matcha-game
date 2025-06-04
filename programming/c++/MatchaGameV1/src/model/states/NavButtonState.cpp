/*
 */
#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
#include "NavButtonState.hpp"
#include "sdl_rect_utils.h"

void NavButtonState::handleInput(Sprite* sprite, const SDL_Event &input) {
    if (input.type == SDL_EVENT_MOUSE_BUTTON_DOWN and sprite->getState() != PRESSED) { // mouse down click
        // get sprite rectangle
        Posn posn = Posn(input.button.x, input.button.y);
        Posn spritePosn = sprite->getPosn();
        SpriteSheet* spriteSheet = sprite->getSheet(sprite->getState());
        float sheetWidth = spriteSheet->getWidth() / spriteSheet->getTotalFr();
        SDL_FRect spriteRect = {spritePosn.getX(), spritePosn.getY(), sheetWidth, spriteSheet->getHeight()};
        // if the click posn is within the sprite rect, set the state
        if (isPosnOverRect(posn, spriteRect)) {
            sprite->setState(STATE::PRESSED);
        }
    } else // NO MOUSE CLICK OR RESET FOR THE LONG PRESS CASE
    {
        sprite->setState(STATE::IDLE);
    }
}

void NavButtonState::update(Sprite* sprite) {
    // delegates to command
    STATE currState = sprite->getState();
    switch (currState) {
        case IDLE: {
            break;
        }
        case WALKING: {
            break;
        }
        case BLINKING: {
            break;
        }
        case RUNNING: {
            break;
        }
        case DRINKING: {
            break;
        }
        case TRANSLATE: {
            break;
        }
        case PRESSED: {
            // NAVIGATE BISH
            ScreenModel* currActiveScreen = screenNav->getMainScreen();
            if (currActiveScreen != screenToNavTo) { // if we are not yet on the screen to go to
                screenNav->setMainScreen(screenToNavTo);
            } else {
                std::cout << "We are already at the screen to navigate to. [NavButtonState]\n";
            }
            sprite->setState(STATE::IDLE);
            break;
        }
        case NONE: {
            break;
        }
    }
}

void NavButtonState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    std::cout << "Draw call for sprite ptr:  " << sprite << ". [NavButtonState]\n";
    std::cout << "sprite state:  " << sprite->getState() << ". [NavButtonState]\n";
    std::cout << "sprite dir:  " << sprite->getStateDir() << ". [NavButtonState]\n";
    bool success = 0;
    // acquire sprite data
    std::cout << "sprite rect call. [NavButtonState]\n";

    std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
    std::cout << "sprite data call. [NavButtonState]\n";
    SpriteStruct spriteData = sprite->getData();
    
    SpriteSheet* sheet = spriteData.sheet;
    SDL_Rect frameRect = std::get<0>(rects);
    SDL_Rect destRect = std::get<1>(rects);
    
    // draw based on direction
    switch (spriteData.dir) {
        case LEFT: {
            success = SDL_BlitSurface(sheet->getSrfcL(), &frameRect, windowSrfc, &destRect);
            if (success < 1) {
                fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
            }
            break;
        }
        case RIGHT: {
            success = SDL_BlitSurface(sheet->getSrfcR(), &frameRect, windowSrfc, &destRect);
            if (success < 1) {
                fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
            }
            break;
        }
        case UP: {
            break;
        }
        case DOWN: {
            break;
        }
    }
}
