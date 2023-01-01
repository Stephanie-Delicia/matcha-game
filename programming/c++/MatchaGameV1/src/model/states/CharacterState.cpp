#include <SDL3/SDL.h>
#include "CharacterState.hpp"
#include "Sprite.hpp"
#include <iostream>

/*
 A class representing the command for handling the walking state for a sprite.
 */
void CharacterState::handleInput(Sprite *sprite, const SDL_Event &input) {
    // std::cout << "input type for handleInput: " << input.type << "\n";
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
    // delegates to command
    // std::cout << "current state in charState for update: " << currState << "\n";
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

void CharacterState::setState(STATE state) {
    currState = state;
}
