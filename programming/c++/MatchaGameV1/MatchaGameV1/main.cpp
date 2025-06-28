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
#include "MainCatcherState.hpp"
#include "NameSpriteMap.hpp"
#include "MenuButtonState.hpp"
#include "ExitButtonState.hpp"
#include "ReturnButtonState.hpp"
#include "InstructionsButtonState.hpp"
#include "MainSprite.hpp"
#include "CharacterState.hpp"
#include "NavButtonState.hpp"
#include "ReplayButtonState.hpp"
#include "ScreenNavigator.hpp"
#include "SpriteSheet.hpp"
#include "IdleState.hpp"
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
    
    CharacterState charStateHandler = CharacterState(640, 360);
    MainCatcherState catcherStateHandler = MainCatcherState(640, 360);
    IdleState idleStateHandler = IdleState();
    
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
    MenuButtonState menuButtonHandler = MenuButtonState();
    ReturnButtonState returnButtonHandler = ReturnButtonState();
    ExitButtonState exitButtonStateHandler = ExitButtonState();
    InstructionsButtonState instructionsButtonStateHandler = InstructionsButtonState();
    
    Sprite* replay_btn = spriteMap.getSprite(REPLAY_BUTTON);
    replay_btn->setStateHandler(&replayButtonHandler);
    replay_btn->setState(NONE);
    replay_btn->setDir(LEFT);
    replay_btn->setPosn(495, 50);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(replay_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(replay_btn);
    
    std::cout << "Checking that all sprites were loaded into gameplay's main properly: [main]\n";
    std::cout << "replay button: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(replay_btn) << ". \n";
    
    player->setStateHandler(&catcherStateHandler);
//    player->setStateHandler(&charStateHandler); // old
    player->setState(IDLE);
    player->setDir(RIGHT);
    player->setPosn(0, 267.00);
    
    std::cout << "player sprite: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(player) << ". \n";
    
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
    
    /*
     Adding the menu button and box
     
     TODO: We have an issue, so, I just remember that we should technically be handling input for both the char's
     continuous keyboard inputs as well as mouse inputs.
     
     So, I think what we need to do is to have a handle input in the main game loop again, BUT, we must NOT handle
     input for the main char! Without this, we cannot take button input for gameplay.
     
     Input for the main char needs to occur outside the loop.
     */
    
    NavButtonState navButtonHandlerMenu = NavButtonState(); // set the param
    navButtonHandlerMenu.setScreenToNavTo(screenNav.getScreen(START_SCREEN));
    
    Sprite* menu_btn = spriteMap.getSprite(MENU_BUTTON);
    std::cout << "menu button: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(menu_btn) << ". \n";
    menu_btn->setStateHandler(&menuButtonHandler);
    menu_btn->setState(IDLE);
    menu_btn->setDir(LEFT);
    menu_btn->setPosn(520, 15);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(menu_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(menu_btn);
    
    Sprite* menu_box = spriteMap.getSprite(MENU_BOX);
    std::cout << "menu_box: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(menu_box) << ". \n";
    menu_box->setStateHandler(&idleStateHandler);
    menu_box->setState(NONE);
    menu_box->setDir(LEFT);
    menu_box->setPosn(179, 76);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(menu_box);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(menu_box);

//
    Sprite* return_btn = spriteMap.getSprite(RETURN_BUTTON);
    return_btn->setStateHandler(&returnButtonHandler);
    return_btn->setState(NONE);
    return_btn->setDir(LEFT);
    return_btn->setPosn(420, 80);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(return_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(return_btn);
//
    Sprite* back_to_start_scrn_btn = spriteMap.getSprite(BACK_TO_START_SCRN_BTN);
    back_to_start_scrn_btn->setStateHandler(&navButtonHandlerMenu);
    back_to_start_scrn_btn->setState(NONE);
    back_to_start_scrn_btn->setDir(LEFT);
    back_to_start_scrn_btn->setPosn(240, 100);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(back_to_start_scrn_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(back_to_start_scrn_btn);
//
    Sprite* exit_btn = spriteMap.getSprite(EXIT_BUTTON);
    std::cout << "exit_btn: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(exit_btn) << ". \n";
    exit_btn->setStateHandler(&exitButtonStateHandler);
    exit_btn->setState(NONE);
    exit_btn->setDir(LEFT);
    exit_btn->setPosn(240, 160);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(exit_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(exit_btn);
//
    Sprite* instructions_btn = spriteMap.getSprite(INSTRUCTIONS_BTN);
    instructions_btn->setStateHandler(&instructionsButtonStateHandler);
    instructions_btn->setState(NONE);
    instructions_btn->setDir(LEFT);
    instructions_btn->setPosn(240, 220);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(instructions_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(instructions_btn);
//
    Sprite* instructions_box = spriteMap.getSprite(INSTRUCTIONS_BOX);
    instructions_box->setStateHandler(&idleStateHandler);
    instructions_box->setState(NONE);
    instructions_box->setDir(LEFT);
    instructions_box->setPosn(72, 111);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(instructions_box);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(instructions_box);

    menu_btn->setSheetMap(&sheetMap);
    menu_box->setSheetMap(&sheetMap);
    return_btn->setSheetMap(&sheetMap);
    back_to_start_scrn_btn->setSheetMap(&sheetMap);
    exit_btn->setSheetMap(&sheetMap);
    instructions_btn->setSheetMap(&sheetMap);
    instructions_box->setSheetMap(&sheetMap);
    
    // end
    
    CatcherController controller = CatcherController(&model, &view);
    controller.setScreenNav(&screenNav);
    std::cout << "Instantiated MVC. (yay!) [main]\n";
    navButtonHandler.setGameController(&controller);
    replayButtonHandler.setGameController(&controller);
    charStateHandler.setGameController(&controller);
    catcherStateHandler.setGameController(&controller);
    menuButtonHandler.setGameController(&controller);
    idleStateHandler.setGameController(&controller);
    navButtonHandlerMenu.setGameController(&controller);
    returnButtonHandler.setGameController(&controller);
    exitButtonStateHandler.setGameController(&controller);
    instructionsButtonStateHandler.setGameController(&controller);
    
    // begin gameplay
    controller.startGame();
    std::cout << "Game closed. [main]\n";
}
