#include <cmath>
#include <iostream>
#include <SDL3/SDL.h>
#include "STATE.h"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "DIRECTION.h"
#include "SpriteStruct.hpp"
#include "CharacterState.hpp"
#include "sdl_rect_utils.h"


/*
 A class representing the command for handling the walking state for a sprite.
 */
void CharacterState::handleInput(Sprite* sprite, const SDL_Event &input) {
    // std::cout << "handleInput call. [CharacterState]" <<  "\n";
    // std::cout << "input type for handleInput: " << input.type << "\n";
    STATE currState = sprite->getState();
    switch (input.type) {
        case SDL_EVENT_KEY_DOWN: {
            const bool *keys = SDL_GetKeyboardState(nullptr);
            // std::cout << "keys[SDL_SCANCODE_LEFT]: " << keys[SDL_SCANCODE_LEFT] << "\n";
            if (keys[SDL_SCANCODE_UP] == 1)
            {
                sprite->setState(STATE::IDLE);
                currState = IDLE;
                sprite->setDir(DIRECTION::UP);
            }
            else if (keys[SDL_SCANCODE_DOWN] == 1)
            {
                sprite->setState(STATE::IDLE);
                currState = IDLE;
                sprite->setDir(DIRECTION::DOWN);
            }
            else if (keys[SDL_SCANCODE_LEFT] == 1)
            {
                sprite->setState(STATE::WALKING);
                currState = WALKING;
                sprite->setDir(DIRECTION::LEFT);
            }
            else if (keys[SDL_SCANCODE_RIGHT] == 1)
            {
                sprite->setState(STATE::WALKING);
                currState = WALKING;
                sprite->setDir(DIRECTION::RIGHT);
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            idleC.update(sprite); // reset frame of state before idle state
            currState = IDLE;
            sprite->setState(STATE::IDLE);
            break;
        }
    }
}

void CharacterState::update(Sprite* sprite) {
    // std::cout << "update call. [CharacterState]" <<  "\n";
    // delegates to command
    // std::cout << "current state in charState for update: " << currState << "\n";
    STATE currState = sprite->getState();
    switch (currState) {
        case IDLE: {
            idleC.update(sprite);
            break;
        }
        case WALKING: {
            walkingC.update(sprite);
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
        case NONE: {
            break;
        }
    }
}

void CharacterState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    // acquire sprite data
    bool success = 0;
    SpriteStruct spriteData = sprite->getData();
    SpriteSheet* sheet = spriteData.sheet;
    std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
    SDL_Rect frameRect = std::get<0>(rects);
    SDL_Rect destRect = std::get<1>(rects);
    
    // draw based on direction
    switch (spriteData.dir) {
        case LEFT: {
            SDL_Surface* srrfc = sheet->getSrfcL();
            success = SDL_BlitSurface(sheet->getSrfcL(), &frameRect, windowSrfc, &destRect);
            // std::cout << "frameRect: x=" << frameRect.x << ", y=" << frameRect.y << ", w=" << frameRect.w << ", h=" << frameRect.h << "\n";
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
