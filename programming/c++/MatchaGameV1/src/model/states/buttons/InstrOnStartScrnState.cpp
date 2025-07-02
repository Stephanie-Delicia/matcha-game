/*
 */
#include <cmath>
#include <iostream>
#include <tuple>
#include <deque>
#include <map>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SceneRequest.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
#include "InstrOnStartScrnState.hpp"
#include "sdl_rect_utils.h"
#include "NavRequest.hpp"

void InstrOnStartScrnState::handleInput(Sprite* sprite, const SDL_Event &input) {
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

void InstrOnStartScrnState::update(Sprite* sprite) {
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
            // reset the game
            // reset the game
            // Pause the game and have the UI for the menu present
            NameSpriteMap* nameSpriteMap = gameController->getModel()->getNameSpriteMap();
            Sprite* title_card = nameSpriteMap->getSprite(BETA_TITLE_CARD);
            Sprite* winnie_drinking = nameSpriteMap->getSprite(WINNIE_DRINKING);
            Sprite* start_button = nameSpriteMap->getSprite(START_BUTTON_TEST);
            Sprite* sm_exit_btn = nameSpriteMap->getSprite(SMALL_EXIT_BUTTON);
            Sprite* start_instr_btn = nameSpriteMap->getSprite(HOW_TO_PLAY_START_BTN);
            
            /*
             Need to make the map D:
             */
            std::tuple<STATE, DIRECTION, float, float, float> exitBtnAnim(TRANSLATE, RIGHT, 15, 884, 0);
            std::tuple<STATE, DIRECTION, float, float, float> winnieAnim(TRANSLATE, RIGHT, 15, 780, 0);
            std::tuple<STATE, DIRECTION, float, float, float> howToBtnAnim(TRANSLATE, RIGHT, 15, 884, 0);
            std::tuple<STATE, DIRECTION, float, float, float> titleCardAnim(TRANSLATE, RIGHT, 15, 712, 0);
            std::tuple<STATE, DIRECTION, float, float, float> startBtnAnim(TRANSLATE, RIGHT, 15, 864, 0);
            
            // to go back
            std::tuple<STATE, DIRECTION, float, float, float> exitBtnAnim2(TRANSLATE, LEFT, 15, 284, 0);
            std::tuple<STATE, DIRECTION, float, float, float> winnieAnim2(TRANSLATE, LEFT, 15, 180, 0);
            std::tuple<STATE, DIRECTION, float, float, float> howToBtnAnim2(TRANSLATE, LEFT, 15, 284, 0);
            std::tuple<STATE, DIRECTION, float, float, float> titleCardAnim2(TRANSLATE, LEFT, 15, 112, 0);
            std::tuple<STATE, DIRECTION, float, float, float> startBtnAnim2(TRANSLATE, LEFT, 15, 264, 0);
            
            // to set their states back to idle
            std::tuple<STATE, DIRECTION, float, float, float> idleReset(IDLE, LEFT, 2, 0, 0);
            
//            // to chill a bit
            std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> spriteAnimMap = {
                {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{titleCardAnim}},
                {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{winnieAnim}},
                {start_button,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{startBtnAnim}},
                {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{exitBtnAnim}},
                {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{howToBtnAnim}}
            };
            std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> spriteAnimMap2 = {
                {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{titleCardAnim2}},
                {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{winnieAnim2}},
                {start_button,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{startBtnAnim2}},
                {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{exitBtnAnim2}},
                {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{howToBtnAnim2}}
            };
            
            std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> idleAnimeMap = {
                {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {start_button,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}}
            };
            
            SceneRequest* moveScreenElemsForInstrIdle = new SceneRequest(NO_INPUT_HANDLING, 0.0);
            moveScreenElemsForInstrIdle->setAnimMap(idleAnimeMap);
            gameController->addRequest(moveScreenElemsForInstrIdle);
            
            SceneRequest* moveScreenElemsForInstr2 = new SceneRequest(NO_INPUT_HANDLING, 0.0);
            moveScreenElemsForInstr2->setAnimMap(spriteAnimMap2);
            gameController->addRequest(moveScreenElemsForInstr2);
            
            SceneRequest* moveScreenElemsForInstr1 = new SceneRequest(NO_INPUT_HANDLING, 0.0);
            moveScreenElemsForInstr1->setAnimMap(spriteAnimMap);
            gameController->addRequest(moveScreenElemsForInstr1);
            
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

void InstrOnStartScrnState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
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
