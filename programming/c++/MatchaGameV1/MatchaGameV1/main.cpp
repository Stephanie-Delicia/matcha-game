/*
    In this latest update, we have a catcher game. The player must move the sprite around using
    key arrows.
 
    Additionally, I plan to add a start screen (not finalized design-wise) in which the player can click the
    "START" button to navigate to the gameplay screen.
 
    You can't go back after this lol, just exit the window
 */
#include <stdio.h>
#include <iostream>
#include "NameStateSheetMap.hpp"
#include "NameSpriteMap.hpp"
#include "CharacterState.hpp"
#include "NavButtonState.hpp"
#include "ReplayButtonState.hpp"
#include "ScreenNavigator.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"
#include "CatcherGameModel.hpp"
#include "CatcherController.hpp"

int main(int argc, char* argv[]) {
    // Sheet map
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    std::cout << "Loaded NameStateSheetMap. [main]\n";
    
    // Sprite map
    NameSpriteMap spriteMap;
    spriteMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData.json");
    spriteMap.setSheetMapAll(&sheetMap);
    std::cout << "Loaded NameSpriteMap. [main]\n";
    
    // Screen navigator
    ScreenNavigator screenNav = ScreenNavigator();
    screenNav.setNameSpriteMap(&spriteMap);
    
    // TODO: nav should through an error if you attemot loadJSON without setting SpriteMap.
    screenNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData2.json");
    std::cout << "Loaded ScreenNavigator. [main]\n";
    
    // ensure view, model, and controller are instantiated with everything they need.
    GameView view;
    CatcherGameModel model = CatcherGameModel(640, 360, "Catch the matcha!");
    // load model with data
    model.setScreenNav(&screenNav);
    model.setNameToSheetMap(&sheetMap);
    model.setNameToSpriteMap(&spriteMap);
    
    // set main player, pleasant sky, test start screen, and test start screen button
    NavButtonState navButtonHandler = NavButtonState(); // set the param
    navButtonHandler.setScreenToNavTo(screenNav.getScreen(GAMEPLAY_SCREEN));
    
    CharacterState charStateHandler = CharacterState();
    
    Sprite* player = spriteMap.getSprite(WINNIE);
    Sprite* start_button = spriteMap.getSprite(START_BUTTON_TEST);
    
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(player);
    screenNav.getScreen(START_SCREEN)->addToUpdate(start_button);
    
    Sprite* bg = spriteMap.getSprite(PLEASANT_SKY);
    Sprite* start_bg = spriteMap.getSprite(START_SCREEN_TEST);
    
    Sprite* black_screen = spriteMap.getSprite(BLACK_SCREEN);
    black_screen->setStateHandler(&charStateHandler);
    black_screen->setState(IDLE);
    black_screen->setDir(LEFT);
    
    ReplayButtonState replayButtonHandler = ReplayButtonState();
    
    Sprite* replay_btn = spriteMap.getSprite(REPLAY_BUTTON);
    replay_btn->setStateHandler(&replayButtonHandler);
    replay_btn->setState(NONE);
    replay_btn->setDir(LEFT);
    replay_btn->setPosn(475, 15);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(replay_btn);
    
    player->setStateHandler(&charStateHandler);
    player->setState(IDLE);
    player->setDir(RIGHT);
    player->setPosn(0, 267.00);
    
    start_button->setStateHandler(&navButtonHandler);
    start_button->setState(IDLE);
    start_button->setPosn(260, 220.00);
    
    model.setMainPlayer(player);
    
    bg->setStateHandler(&charStateHandler);
    start_bg->setStateHandler(&charStateHandler);
    bg->setState(IDLE);
    start_bg->setState(IDLE);
    bg->setPosn(0, 0);
    start_bg->setPosn(0, 0);
    
    player->setSheetMap(&sheetMap);
    start_button->setSheetMap(&sheetMap);
    replay_btn->setSheetMap(&sheetMap);
    bg->setSheetMap(&sheetMap);
    start_bg->setSheetMap(&sheetMap);
    
    CatcherController controller = CatcherController(&model, &view);
    controller.setScreenNav(&screenNav);
    std::cout << "Instantiated MVC. (yay!) [main]\n";
    navButtonHandler.setGameController(&controller);
    replayButtonHandler.setGameController(&controller);
    
    
    // begin gameplay
    controller.startGame();
    std::cout << "Game closed. [main]\n";
}
