#include "CharacterState.hpp"
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
    bool isSpacePressed = keys[SDL_SCANCODE_SPACE];
    bool keyDown = (isUpPressed || isDownPressed || isLeftPressed || isRightPressed || isSpacePressed); // are any of these pressed down?
    if (keyDown) {
            if (isLeftPressed && isRightPressed)
            {
                if (sprite->getState() != JUMPING) {
                    sprite->setState(STATE::WALKING);
                }
            }
            else if (isLeftPressed)
            {
                // consider if the char state is JUMPING
                // then we need to fulfill the full jumping animation also and not change state yet
                // if sprite state is jumping,
                // do not change state but still set the direction
                if (sprite->getState() != JUMPING) {
                    sprite->setState(STATE::WALKING);
                }
                sprite->setDir(DIRECTION::LEFT);
            }
            else if (isRightPressed)
            {
                if (sprite->getState() != JUMPING) {
                    sprite->setState(STATE::WALKING);
                }
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
            else if (isSpacePressed) {
                std::cout << "I get to here." << " [CharState, checking for jumping.]\n";
                setJumpingCommand();
                std::cout << "timer ptr: " << gameController->getTimer() << ". [charstate, checking for jumping.]\n";
                sprite->setState(STATE::JUMPING);
                sprite->setDir(sprite->getStateDir());
            }
        } else // NO KEY IS PRESSED
        {
            if (sprite->getState() != JUMPING) {
                idleC.update(sprite); // reset frame of state before idle state
                sprite->setState(STATE::IDLE);
            }
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
        case HOVER: {
            break;
        }
        case JUMPING: {
            std::cout << "I get to here." << " [CharState, checking for jumping update.]\n";
            jumpingC.update(sprite);
            break;
        }
        case NONE: {
            break;
        }
        default: {
            break;
        }
    }
}

void CharacterState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    // draw based on direction, IF THE STATE IS NOT NONE
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
