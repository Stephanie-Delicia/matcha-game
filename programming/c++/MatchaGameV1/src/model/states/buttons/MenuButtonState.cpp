/*
 */
#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SceneRequest.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
#include "MenuButtonState.hpp"
#include "sdl_rect_utils.h"
#include "NavRequest.hpp"

void MenuButtonState::handleInput(Sprite* sprite, const SDL_Event &input) {
    // get mouse posn
    float mouse_x, mouse_y;
    SDL_MouseButtonFlags mouse_state;

    // Get the mouse state
    mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);

    if (sprite->getState() != NONE) {
        if (SDL_EVENT_MOUSE_BUTTON_DOWN == input.type and sprite->getState() != PRESSED) { // mouse down click
            // get sprite rectangle
            Posn posn = Posn(input.button.x, input.button.y);
            Posn spritePosn = sprite->getPosn();
            SpriteSheet* spriteSheet = sprite->getSheet(sprite->getState());
            float sheetWidth = spriteSheet->getWidth() / spriteSheet->getTotalFr();
            SDL_FRect spriteRect = {spritePosn.getX(), spritePosn.getY(), sheetWidth + 5, spriteSheet->getHeight() + 5};
            // if the click posn is within the sprite rect, set the state
            if (isPosnOverRect(posn, spriteRect)) {
                sprite->setState(STATE::PRESSED);
            }
        } else // NO MOUSE CLICK OR RESET FOR THE LONG PRESS CASE
        {
            // check if the mouse is hovering over a button
            Posn posn = Posn(mouse_x, mouse_y);
            Posn spritePosn = sprite->getPosn();
            SpriteSheet* spriteSheet = sprite->getSheet(sprite->getState());
            float sheetWidth = spriteSheet->getWidth() / spriteSheet->getTotalFr();
            SDL_FRect spriteRect = {spritePosn.getX(), spritePosn.getY(), sheetWidth + 5, spriteSheet->getHeight() + 5};
            // if the click posn is within the sprite rect, set the state to hover
            if (isPosnOverRect(posn, spriteRect)) {
                sprite->setState(STATE::HOVER);
            } else {
                sprite->setState(STATE::IDLE);
            }
        }
    }
}

void MenuButtonState::update(Sprite* sprite) {
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
            // reset the game
            // Pause the game and have the UI for the menu present
            NameSpriteMap* nameSpriteMap = gameController->getModel()->getNameSpriteMap();
            Sprite* menuBox = nameSpriteMap->getSprite(MENU_BOX);
            Sprite* returnToStartBtn = nameSpriteMap->getSprite(BACK_TO_START_SCRN_BTN);
            Sprite* exitBtn = nameSpriteMap->getSprite(EXIT_BUTTON);
            Sprite* instructionsBtn = nameSpriteMap->getSprite(INSTRUCTIONS_BTN);
            Sprite* menuReturnBtn = nameSpriteMap->getSprite(RETURN_BUTTON);

            if (sprite->getState() != NONE) {
                sprite->setState(NONE);
            } else {
                sprite->setState(IDLE);
            }
            // set all of them to idle to display
            menuBox->setState(IDLE);
            returnToStartBtn->setState(IDLE);
            exitBtn->setState(IDLE);
            instructionsBtn->setState(IDLE);
            std::cout << "Return btn posn" << menuReturnBtn->getPosn().getX() << ", " << menuReturnBtn->getPosn().getY() << ". [menu btn state()]\n";
            menuReturnBtn->setPosn(420, 80);
            menuReturnBtn->setState(IDLE);
            
            // button goes to normal now
            // TODO: a conditional here for if the game has been beaten yet.
            // If so, then do not add this request, otherwise, do add it to pause the game.
            // Add or statement for if there is a scene playing?!
            // Because say I press the menu button a bunch of times, now it has so many eternal still requests!
            if (!gameController->isGameBeaten()) {
                gameController->addRequest(new SceneRequest(STILL, -1));
            } else { // game is beaten, don't add a new request please!
                
            }
            
            break;
        }
        case HOVER: {
            break;
        }
        case NONE: {
            break;
        }
    }
}

void MenuButtonState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    // draw based on direction
    if (sprite->getState() != NONE) {
        bool success = 0;
        // acquire sprite data
        std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
        SpriteStruct spriteData = sprite->getData();
        
        SpriteSheet* sheet = spriteData.sheet;
        SDL_Rect frameRect = std::get<0>(rects);
        SDL_Rect destRect = std::get<1>(rects);
        
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
}
