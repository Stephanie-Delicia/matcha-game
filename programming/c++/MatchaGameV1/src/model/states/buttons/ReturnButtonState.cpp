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
#include "ReturnButtonState.hpp"
#include "sdl_rect_utils.h"
#include "NavRequest.hpp"

void ReturnButtonState::handleInput(Sprite* sprite, const SDL_Event &input) {
    if (sprite->getState() != NONE) {
        // get mouse posn
        float mouse_x, mouse_y;
        SDL_MouseButtonFlags mouse_state;

        // Get the mouse state
        mouse_state = SDL_GetMouseState(&mouse_x, &mouse_y);
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

void ReturnButtonState::update(Sprite* sprite) {
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
            transC.update(sprite);
            break;
        }
        case PRESSED: {
            // Pause the game and have the UI for the menu present
            NameSpriteMap* nameSpriteMap = gameController->getModel()->getNameSpriteMap();
            Sprite* menuBox = nameSpriteMap->getSprite(MENU_BOX);
            Sprite* returnToStartBtn = nameSpriteMap->getSprite(BACK_TO_START_SCRN_BTN);
            Sprite* exitBtn = nameSpriteMap->getSprite(EXIT_BUTTON);
            Sprite* instructionsBtn = nameSpriteMap->getSprite(INSTRUCTIONS_BTN);
            Sprite* menuReturnBtn = nameSpriteMap->getSprite(RETURN_BUTTON);
            Sprite* instructionsBox = nameSpriteMap->getSprite(INSTRUCTIONS_BOX);
            Sprite* menuBtn = nameSpriteMap->getSprite(MENU_BUTTON);
            

            
            if (gameController->getModel()->getActiveScreen()->screenType() == START_SCREEN) {
                // roll back
                Sprite* title_card = nameSpriteMap->getSprite(BETA_TITLE_CARD);
                Sprite* winnie_drinking = nameSpriteMap->getSprite(WINNIE_DRINKING);
                Sprite* start_button = nameSpriteMap->getSprite(START_BUTTON_TEST);
                Sprite* sm_exit_btn = nameSpriteMap->getSprite(SMALL_EXIT_BUTTON);
                Sprite* start_instr_btn = nameSpriteMap->getSprite(HOW_TO_PLAY_START_BTN);
                Sprite* instr_box = nameSpriteMap->getSprite(INSTRUCTIONS_BOX);
                Sprite* return_btn = nameSpriteMap->getSprite(RETURN_BUTTON);
                
                std::tuple<STATE, DIRECTION, float, float, float> exitBtnAnim2(TRANSLATE, LEFT, 18, 284, 0);
                std::tuple<STATE, DIRECTION, float, float, float> winnieAnim2(TRANSLATE, LEFT, 18, 180, 0);
                std::tuple<STATE, DIRECTION, float, float, float> howToBtnAnim2(TRANSLATE, LEFT, 18, 284, 0);
                std::tuple<STATE, DIRECTION, float, float, float> titleCardAnim2(TRANSLATE, LEFT, 18, 112, 0);
                std::tuple<STATE, DIRECTION, float, float, float> startBtnAnim2(TRANSLATE, LEFT, 18, 264, 0);
                std::tuple<STATE, DIRECTION, float, float, float> instr_boxBtnAnim(TRANSLATE, LEFT, 18, -528, 0);
                std::tuple<STATE, DIRECTION, float, float, float> returnBtnAnim(TRANSLATE, LEFT, 18, -100, 0);
                
                std::tuple<STATE, DIRECTION, float, float, float> idleReset(IDLE, LEFT, 2, 0, 0);
                
                std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> spriteAnimMap2 = {
                    {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{titleCardAnim2}},
                    {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{winnieAnim2}},
                    {start_button,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{startBtnAnim2}},
                    {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{exitBtnAnim2}},
                    {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{howToBtnAnim2}},
                    {instr_box, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{instr_boxBtnAnim}},
                    {return_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{returnBtnAnim}}
                };
                
                std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> idleAnimeMap = {
                    {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {start_button,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {instr_box, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                    {return_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}}
                };
                
                SceneRequest* moveScreenElemsForInstrIdle = new SceneRequest(NO_INPUT_HANDLING, 0.0);
                moveScreenElemsForInstrIdle->setAnimMap(idleAnimeMap);
                gameController->addRequest(moveScreenElemsForInstrIdle);
                
                SceneRequest* moveScreenElemsForInstr2 = new SceneRequest(NO_INPUT_HANDLING, 0.0);
                moveScreenElemsForInstr2->setAnimMap(spriteAnimMap2);
                gameController->addRequest(moveScreenElemsForInstr2);
            } else {
                if (menuBtn->getState() == NONE) {
                    menuBtn->setState(IDLE);
                }
                
                // Check if the menu box or the instructions box is open
                if (menuBox->getState() != NONE) {
                    menuBox->setState(NONE);
                    returnToStartBtn->setState(NONE);
                    exitBtn->setState(NONE);
                    instructionsBtn->setState(NONE);
                    menuReturnBtn->setState(NONE);
                } else { // instructions box is open
                    menuReturnBtn->setState(NONE);
                    menuReturnBtn->setPosn(420, 80); // set to original posn
                    instructionsBox->setState(NONE);
                }
                
                if (!gameController->isGameBeaten()) {
                    gameController->setEndScene(true);
                }
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

void ReturnButtonState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
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
