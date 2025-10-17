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
#include "IdleState.hpp"
#include "sdl_rect_utils.h"
#include "NavRequest.hpp"

void IdleState::handleInput(Sprite* sprite, const SDL_Event &input) {
    // nothing!
    // this processes absolutely nothing
}

void IdleState::update(Sprite* sprite) {
    float currFrameTime = sprite->getCurrFrameTime();
    STATE currState = sprite->getState();
    switch (currState) {
        case VICTORY_POSE: {
            if (currFrameTime <= 0.0) { // if enough time passed to get to the next frame
                sprite->updateSheet(sprite->getState(), 1); // go to next frame by incrementing frame #
            }
            break;
        }
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
            break;
        }
        case HOVER: {
            break;
        }
        case JUMPING: {
            break;
        }
        case SCROLLING_BANNER: {
            transC.update(sprite);
            // apply mod width operator!! To the x-posn
            Posn pos = sprite->getPosn();
            SpriteSheet* sheet = sprite->getSheet(sprite->getState());
            float width = sheet->getWidth() / sheet->getTotalFr();
            float newX;
            // modulus almost, to complete circular drawing
            if (pos.getX() == width) {
                newX = 0;
            } else if (pos.getX() > width) {
                int multiplier = std::round(pos.getX() / width);
                newX = pos.getX() - (multiplier * width);
            } else if (pos.getX() < 0) {
                int multiplier = std::round(pos.getX() / width);
                float intermed = pos.getX() - (multiplier * width);
                newX = width + intermed;
            } else {
                newX = pos.getX();
            }
            sprite->setPosn(newX, pos.getY());
            break;
        }
        case DIAGONAL_BANNER: {
            // Update x and y given an angle
            // Should sprite have an angle param? to make this easier
            // then update x and y given this
            // so, determine x and y given the angle, where speed will be the hypotenuse
            float oppositeY = std::round(std::sin(sprite->getAngle()) * sprite->getFrameSpeed());
            float adjacentX = std::round(std::cos(sprite->getAngle()) * sprite->getFrameSpeed());
            sprite->setPosn(sprite->getPosn().getIntX() + adjacentX, sprite->getPosn().getIntY() + oppositeY);
            
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

void IdleState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    // draw based on direction
    if (sprite->getState() != NONE) {
        bool success = 0;
        bool success1 = 0;
        bool success2 = 0;
        // acquire sprite data
        std::tuple<SDL_Rect, SDL_Rect> rects = sprite->getSrcAndDest();
        SpriteStruct spriteData = sprite->getData();
        
        SpriteSheet* sheet = spriteData.sheet;
        SDL_Rect frameRect = std::get<0>(rects);
        SDL_Rect destRect = std::get<1>(rects);
        Posn pos = sprite->getPosn();
        
        if (sprite->getAlpha() < 1) {
            SDL_SetSurfaceAlphaMod(sheet->getSrfcL(), sprite->getAlpha() * 255.00);
        } else {
            SDL_SetSurfaceAlphaMod(sheet->getSrfcL(), 255.00);
        }
        
        // how do we do this?
        // do we base the split off of the x-posn?
        // if we are scrolling to the right, for example, the x-posn is essentially where the split occurs,
        // Assume sprite is in SCROLLING_BANNER, only to the left or right.
        // This is just a matter, then, of creating the correct rectangles and blitzing both
        // We need to also make sure that the x-posn is circular, it never is outside of the screen.
        
        switch (spriteData.dir) {
            case LEFT: {
                if (sprite->getState() == SCROLLING_BANNER) {
                    // A = from 0 to x rect, B = then x to width rect
                    // Blitz B from the left, then A to the right
                    // Rectangle A
                    SDL_Rect rectA = roundRect({0, 0, sprite->getPosn().getX(), sheet->getHeight()});
                    SDL_Rect rectB = roundRect({sprite->getPosn().getX(), 0, sheet->getWidth(), sheet->getHeight()});
                    SDL_Rect destB = roundRect({0, pos.getY(), sheet->getWidth() - sprite->getPosn().getX(), 0.0});
                    SDL_Rect destA = roundRect({sheet->getWidth() - sprite->getPosn().getX(), pos.getY(), sheet->getWidth(), 0.0});
                    success1 = SDL_BlitSurface(sheet->getSrfcL(), &rectA, windowSrfc, &destA);
                    success2 = SDL_BlitSurface(sheet->getSrfcL(), &rectB, windowSrfc, &destB);
                } else {
                    success = SDL_BlitSurface(sheet->getSrfcL(), &frameRect, windowSrfc, &destRect);
                    if (success < 1) {
                        fprintf(stderr, "SDL_BlitSurface failed! SDL_Error: %s\n", SDL_GetError());
                    }
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
