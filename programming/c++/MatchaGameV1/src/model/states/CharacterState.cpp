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
 Rather than by input.type, use the key states for switch statements instead.
 Reason being that even if I hold one key down, if I WAS holding multiple keys down, but ONE OF THEM is lifted,
 this will automatically return a KEY_UP event. Checking the key array is more accurate and will correctly show which
 keys are still pressed down.
 */
void CharacterState::handleInput(Sprite* sprite, const SDL_Event &input) {
    const bool *keys = SDL_GetKeyboardState(nullptr);
    bool isUpPressed    = keys[SDL_SCANCODE_UP];
    bool isDownPressed  = keys[SDL_SCANCODE_DOWN];
    bool isLeftPressed  = keys[SDL_SCANCODE_LEFT];
    bool isRightPressed = keys[SDL_SCANCODE_RIGHT];
    bool keyDown = (isUpPressed || isDownPressed || isLeftPressed || isRightPressed); // are any of these pressed down?
    if (keyDown) {
            if (isLeftPressed && isRightPressed)
            {
                sprite->setState(STATE::WALKING);

            }
            else if (isLeftPressed)
            {
                sprite->setState(STATE::WALKING);
                sprite->setDir(DIRECTION::LEFT);
            }
            else if (isRightPressed)
            {
                sprite->setState(STATE::WALKING);
                sprite->setDir(DIRECTION::RIGHT);
            }
            else if (isUpPressed)
            {
                sprite->setState(STATE::IDLE);
                sprite->setDir(sprite->getStateDir());
            }
            else if (isDownPressed)
            {
                sprite->setState(STATE::IDLE);
                sprite->setDir(sprite->getStateDir());
            }
        } else // NO KEY IS PRESSED
        {
            std::cout << "No key is pressed so player should be made idle. \n";
            idleC.update(sprite); // reset frame of state before idle state
            sprite->setState(STATE::IDLE);
        }
}

void CharacterState::update(Sprite* sprite) {
    // delegates to command
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
        case TRANSLATE: {
            break;
        }
        case PRESSED: {
            break;
        }
        case NONE: {
            break;
        }
    }
}

void CharacterState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    bool success = 0;
    // acquire sprite data
    std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
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

/*
 For debugging:
 
 // std::cout << "frameRect: x=" << frameRect.x << ", y=" << frameRect.y << ", w=" << frameRect.w << ", h=" << frameRect.h << "\n";
 // std::cout << "current state in charState for update: " << currState << "\n";
 // std::cout << "handleInput call. [CharacterState]" <<  "\n";
 // std::cout << "input type for handleInput: " << input.type << "\n";
 // std::cout << "keys[SDL_SCANCODE_LEFT]: " << keys[SDL_SCANCODE_LEFT] << "\n";
 */
