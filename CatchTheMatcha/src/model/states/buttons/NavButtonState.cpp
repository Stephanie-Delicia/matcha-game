
#include "NavButtonState.hpp"

void NavButtonState::handleInput(Sprite* sprite, const SDL_Event &input) {
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

void NavButtonState::update(Sprite* sprite) {
    if (sprite->getState() != NONE) {
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
//                std::cout << "Pressed nav button for sprite: " << sprite->getName() << ". [Nav Button State.]\n";
                NameSpriteMap* nameSpriteMap = gameController->getModel()->getNameSpriteMap();
                Sprite* menuBox = nameSpriteMap->getSprite(MENU_BOX);
                Sprite* returnToStartBtn = nameSpriteMap->getSprite(BACK_TO_START_SCRN_BTN);
                Sprite* exitBtn = nameSpriteMap->getSprite(EXIT_BUTTON);
                Sprite* instructionsBtn = nameSpriteMap->getSprite(INSTRUCTIONS_BTN);
                Sprite* menuReturnBtn = nameSpriteMap->getSprite(RETURN_BUTTON);
                Sprite* instructionsBox = nameSpriteMap->getSprite(INSTRUCTIONS_BOX);
                Sprite* menuBtn = nameSpriteMap->getSprite(MENU_BUTTON);
                Sprite* resumeBtn = nameSpriteMap->getSprite(RESUME_GAME_BTN);
                Sprite* startBtn = nameSpriteMap->getSprite(START_BUTTON_TEST);
//                ScreenNavigator* screenNav = gameController->getModel()->getNavigator();
                
                gameController->setPauseGameBool(true);
//                std::cout << "Paused game. [Nav Button State.]\n";
                
                // if I am on the gameplay screen, then setup
                if (gameController->getModel()->getActiveScreen()->screenType() == GAMEPLAY_SCREEN) {
//                    std::cout << "Pressed nav button on gaemplay screen. [nav button]\n";
                    gameController->getGameplayTimer()->pause();
                    menuBtn->setState(IDLE); // for some reason?
                    sprite->setState(NONE);
                    instructionsBtn->setState(NONE);
                    instructionsBox->setState(NONE);
                    menuBox->setState(NONE);
                    returnToStartBtn->setState(NONE);
                    exitBtn->setState(NONE);
                    menuReturnBtn->setState(NONE);
                    // screenNav->setMainScreen(screenNav->getScreen(START_SCREEN));
                    gameController->setEndScene(true); // end pause when you nav to start screen
                } else if  (gameController->getModel()->getActiveScreen()->screenType() == START_SCREEN) { // on start screen
//                    std::cout << "Pressed nav button on start screen. [nav button]\n";
                    sprite->setState(IDLE);
                    startBtn->setState(NONE);
                    resumeBtn->setState(IDLE);
                    gameController->startGameBool();
                    // I need to somehow access if the player lost
                    if (gameController->didPlayerLose() or gameController->isGameBeaten()) {
//                        std::cout << "Added still scene with inf time duration. [menu btn state]\n";
                        gameController->addRequest(new SceneRequest(STILL, -1));
                    }
                    // TODO: for some reason navigating back when a game is finished replays it when it shouldn't
                }
                
                // make a transition draw request
                std::cout << "Still req." << ". [Nav Button State.]\n";
                SceneRequest* sceneReq2 = new SceneRequest(STILL, 500);
                gameController->addRequest(sceneReq2);
                
                // request a fade out
                std::cout << "Unfade req." << ". [Nav Button State.]\n";
                SceneRequest* unfadeSceneReq = new SceneRequest(UNFADE, 250);
                gameController->addRequest(unfadeSceneReq);

                // make a nav draw request
                std::cout << "nav req." << ". [Nav Button State.]\n";
                NavRequest* navReq = new NavRequest(screenToNavTo);
                gameController->addRequest(navReq);
                
                std::cout << "remove black screen." << ". [Nav Button State.]\n";
                SceneRequest* removeBlackScreenReq = new SceneRequest(REMOVE_BLACK_SCREEN, 0.0);
                gameController->addRequest(removeBlackScreenReq);
                
                std::cout << "Add black screen." << ". [Nav Button State.]\n";
                SceneRequest* addBlackScreenReq = new SceneRequest(ADD_BLACK_SCREEN, screenToNavTo);
                gameController->addRequest(addBlackScreenReq);
                
                // make a transition draw request
                std::cout << "still req." << ". [Nav Button State.]\n";
                SceneRequest* sceneReq = new SceneRequest(STILL, 250);
                gameController->addRequest(sceneReq);
                
                // make a transition draw request
                std::cout << "Fade req." << ". [Nav Button State.]\n";
                SceneRequest* fadeSceneReq = new SceneRequest(FADE, 500);
                gameController->addRequest(fadeSceneReq);
                
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

}

void NavButtonState::draw(Sprite* sprite, SDL_Surface* windowSrfc) {
    if (sprite->getState() != NONE) {
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
}
