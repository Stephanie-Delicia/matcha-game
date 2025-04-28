#include <SDL3/SDL.h>
#include "CharState.hpp"
#include "WalkingState.hpp"
#include "Posn.hpp"
#include "Sprite.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include "StateCommand.hpp"

/*
 A class representing the command for handling the walking state for a sprite.
 */

CharState::CharState() {
}

CharState::~CharState() {
}

void CharState::handleInput(Sprite *sprite, const SDL_Event &input) {
    switch (input.type) {
        case SDL_EVENT_KEY_DOWN: {
            const bool *keys = SDL_GetKeyboardState(nullptr);
            if (keys[SDL_SCANCODE_UP] == 1)
            {
                sprite->setState(STATE::IDLE);
                sprite->setDir(DIRECTION::UP);
            }
            else if (keys[SDL_SCANCODE_DOWN] == 1)
            {
                sprite->setState(STATE::IDLE);
                sprite->setDir(DIRECTION::DOWN);
            }
            else if (keys[SDL_SCANCODE_LEFT] == 1)
            {
                sprite->setState(STATE::WALKING);
                sprite->setDir(DIRECTION::LEFT);
            }
            else if (keys[SDL_SCANCODE_RIGHT] == 1)
            {
                sprite->setState(STATE::WALKING);
                sprite->setDir(DIRECTION::RIGHT);
            }
            break;
        }
        case SDL_EVENT_KEY_UP: {
            idleC.update(sprite); // reset frame of state before idle state
            sprite->setState(STATE::IDLE);
            break;
        }
    }
}

void CharState::update(Sprite* sprite) {
    // delegates to command
    currCommand.update(sprite);
}
