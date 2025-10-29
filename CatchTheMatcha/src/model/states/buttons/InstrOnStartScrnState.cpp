/*
 */

#include "InstrOnStartScrnState.hpp"

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
            Sprite* go_back_to_gameplay_btn;
            if (gameController->didGameStart()) {
                // if game started, assign to resume button, otherwise,no
                go_back_to_gameplay_btn = nameSpriteMap->getSprite(RESUME_GAME_BTN);
            } else {
                go_back_to_gameplay_btn = nameSpriteMap->getSprite(START_BUTTON_TEST);
            }
            Sprite* sm_exit_btn = nameSpriteMap->getSprite(SMALL_EXIT_BUTTON);
            Sprite* start_instr_btn = nameSpriteMap->getSprite(HOW_TO_PLAY_START_BTN);
            Sprite* instr_box = nameSpriteMap->getSprite(INSTRUCTIONS_BOX);
            Sprite* return_btn = nameSpriteMap->getSprite(RETURN_BUTTON);
            Sprite* white_return_btn = nameSpriteMap->getSprite(WHITE_RESUME_BTN);
            
            instr_box->setPosn(-528, 61);
            white_return_btn->setPosn(-66, 63);
            /*
              instr_box -> -528 + 72 = -456
              box has width 500
             so right corner is at x = -28
             so the return btn is -38 from the right corner
             want the return btn at the right corner

             the boxes new posn should be -456
             the right corner is at 44
             so, the new btn pos should be 6
             */
            
            std::tuple<STATE, DIRECTION, float, float, float> exitBtnAnim(TRANSLATE, RIGHT, 18, 884, 0);
            std::tuple<STATE, DIRECTION, float, float, float> winnieAnim(TRANSLATE, RIGHT, 18, 780, 0);
            std::tuple<STATE, DIRECTION, float, float, float> howToBtnAnim(TRANSLATE, RIGHT, 18, 884, 0);
            std::tuple<STATE, DIRECTION, float, float, float> titleCardAnim(TRANSLATE, RIGHT, 18, 712, 0);
            std::tuple<STATE, DIRECTION, float, float, float> startBtnAnim(TRANSLATE, RIGHT, 18, 864, 0);
            std::tuple<STATE, DIRECTION, float, float, float> instr_boxBtnAnim(TRANSLATE, RIGHT, 18, 72, 0);
            std::tuple<STATE, DIRECTION, float, float, float> returnBtnAnim(TRANSLATE, RIGHT, 18, 536, 0);
            
            // to set their states back to idle
            std::tuple<STATE, DIRECTION, float, float, float> idleReset(IDLE, LEFT, 2, 0, 0);
            
//            // to chill a bit
            std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> spriteAnimMap = {
                {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{titleCardAnim}},
                {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{winnieAnim}},
                {go_back_to_gameplay_btn,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{startBtnAnim}},
                {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{exitBtnAnim}},
                {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{howToBtnAnim}},
                {instr_box, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{instr_boxBtnAnim}},
                {white_return_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{returnBtnAnim}}
            };
            
            std::map<Sprite*, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>> idleAnimeMap = {
                {title_card,      std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {winnie_drinking, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {go_back_to_gameplay_btn,    std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {sm_exit_btn,     std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}},
                {start_instr_btn, std::deque<std::tuple<STATE, DIRECTION, float, float, float>>{idleReset}}
            };
            
            // set elements to an idle state
            SceneRequest* moveScreenElemsForInstrIdle = new SceneRequest(NO_INPUT_HANDLING, 0.0);
            moveScreenElemsForInstrIdle->setAnimMap(idleAnimeMap);
            gameController->addRequest(moveScreenElemsForInstrIdle);
            
            // send in anim request to slide elements
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
        default: {
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
