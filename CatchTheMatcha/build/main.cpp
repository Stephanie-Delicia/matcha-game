/*
    This main file loads game data for sprites, sprite sheets, and the game's screen navigator. This game is called "Catch the matcha" where the goal is to catch enough matcha within a time limit.
 */
#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "NameStateSheetMap.hpp"
#include "MainCatcherState.hpp"
#include "NameSpriteMap.hpp"
#include "MenuButtonState.hpp"
#include "InstrOnStartScrnState.hpp"
#include "BoxToCatchState.hpp"
#include "ExitButtonState.hpp"
#include "ReturnButtonState.hpp"
#include "InstructionsButtonState.hpp"
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
#include "CatcherLevelStruct.hpp"
#include "ScreenModel.hpp"

int main(int argc, char* argv[]) {
    const char* execPath = SDL_GetBasePath();
    std::string execPathStr = execPath;
    std::string spriteSheetDataPath = execPathStr + "/../../res/data/test/testSpriteSheetData.json";
    std::string nameSpriteDataPath = execPathStr + "/../../res/data/test/nameSpriteData.json";
    std::string navigatorDataPath = execPathStr + "/../../res/data/test/testScreenNavData2.json";
    
    // Sheet map
    NameStateSheetMap sheetMap;
    sheetMap.readJSON(spriteSheetDataPath);
    std::cout << "Loaded NameStateSheetMap data structure. [main]\n";
    
    // Sprite map
    NameSpriteMap spriteMap;
    spriteMap.loadJSON(nameSpriteDataPath);
    spriteMap.setSheetMapAll(&sheetMap);
    
    std::cout << "Loaded NameSpriteMap data structure. [main]\n";
    
    // Screen navigator
    ScreenNavigator screenNav = ScreenNavigator();
    screenNav.setNameSpriteMap(&spriteMap);
    
    // TODO: nav should through an error if you attempt loadJSON without setting SpriteMap.
    screenNav.loadJSON(navigatorDataPath);
    std::cout << "Loaded ScreenNavigator data structure. [main]\n";
    
    // ensure view, model, and controller are instantiated with everything they need.
    GameView view;
    CatcherGameModel model = CatcherGameModel(640, 360, " ");
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
    sheetMap.getSpriteSheet(WINNIE, WALKING)->setFPSGoal(25);
    sheetMap.getSpriteSheet(WINNIE, LOSE_POSE)->setFPSGoal(24);
    sheetMap.getSpriteSheet(WINNIE, RUNNING)->setFPSGoal(30);
    
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
    InstrOnStartScrnState instrBtnOnStartScrnStateHandler = InstrOnStartScrnState();
    
    Sprite* replay_btn = spriteMap.getSprite(REPLAY_BUTTON);
    replay_btn->setStateHandler(&replayButtonHandler);
    replay_btn->setState(NONE);
    replay_btn->setDir(LEFT);
    replay_btn->setPosn(-100, 50);
//    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(replay_btn);
//    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(replay_btn);
    
    player->setStateHandler(&catcherStateHandler);
    player->setState(IDLE);
    player->setDir(RIGHT);
    player->setPosn(0, 267.00);
    
//    std::cout << "player sprite: " << screenNav.getScreen(GAMEPLAY_SCREEN)->onScreen(player) << ". \n";
    
    start_button->setStateHandler(&navButtonHandler);
    start_button->setState(IDLE);
    start_button->setPosn(269, 190.00);
    
    model.setMainPlayer(player);
    model.setUpStartScreenMatchas();
    
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
    screenNav.getScreen(START_SCREEN)->addToUI(return_btn);
    screenNav.getScreen(START_SCREEN)->addToUpdate(return_btn);
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
    screenNav.getScreen(START_SCREEN)->addToUI(instructions_box);
    screenNav.getScreen(START_SCREEN)->addToUpdate(instructions_box);

    menu_btn->setSheetMap(&sheetMap);
    menu_box->setSheetMap(&sheetMap);
    return_btn->setSheetMap(&sheetMap);
    back_to_start_scrn_btn->setSheetMap(&sheetMap);
    exit_btn->setSheetMap(&sheetMap);
    instructions_btn->setSheetMap(&sheetMap);
    instructions_box->setSheetMap(&sheetMap);
    
    /*
     Adding new start screen elements
     */
    
    Sprite* resume_btn = spriteMap.getSprite(RESUME_BUTTON);
    Sprite* small_exit_btn = spriteMap.getSprite(SMALL_EXIT_BUTTON);
    Sprite* winnie_drinking_ptr = spriteMap.getSprite(WINNIE_DRINKING);
    Sprite* how_to_play_start_btn = spriteMap.getSprite(HOW_TO_PLAY_START_BTN);
    Sprite* title_card_ptr = spriteMap.getSprite(BETA_TITLE_CARD);
    
    resume_btn->setStateHandler(&idleStateHandler); // resume btn
    resume_btn->setState(NONE);
    resume_btn->setDir(LEFT);
    resume_btn->setPosn(20, 20);
    screenNav.getScreen(START_SCREEN)->addToUI(resume_btn);
    screenNav.getScreen(START_SCREEN)->addToUpdate(resume_btn);
    
    small_exit_btn->setStateHandler(&exitButtonStateHandler); // resume btn
    small_exit_btn->setState(IDLE);
    small_exit_btn->setDir(LEFT);
    small_exit_btn->setPosn(284, 260);
    screenNav.getScreen(START_SCREEN)->addToUpdate(small_exit_btn);
    screenNav.getScreen(START_SCREEN)->addToUI(small_exit_btn);
    
    winnie_drinking_ptr->setStateHandler(&idleStateHandler); // resume btn
    winnie_drinking_ptr->setState(IDLE);
    winnie_drinking_ptr->setDir(LEFT);
    winnie_drinking_ptr->setPosn(180, 200);
    screenNav.getScreen(START_SCREEN)->addToUpdate(winnie_drinking_ptr);
    screenNav.getScreen(START_SCREEN)->addToUI(winnie_drinking_ptr);
    
    how_to_play_start_btn->setStateHandler(&instrBtnOnStartScrnStateHandler); // resume btn
    how_to_play_start_btn->setState(IDLE);
    how_to_play_start_btn->setDir(LEFT);
    how_to_play_start_btn->setPosn(284, 230);
    screenNav.getScreen(START_SCREEN)->addToUpdate(how_to_play_start_btn);
    screenNav.getScreen(START_SCREEN)->addToUI(how_to_play_start_btn);
    
    Sprite* blue_sky_ptr = spriteMap.getSprite(CLEAR_BLUE_SKY);
    blue_sky_ptr->setStateHandler(&idleStateHandler);
    blue_sky_ptr->setState(IDLE);
    blue_sky_ptr->setDir(LEFT);
    blue_sky_ptr->setPosn(0, 0);
    
    title_card_ptr->setStateHandler(&idleStateHandler); // resume btn
    title_card_ptr->setState(IDLE);
    title_card_ptr->setDir(LEFT);
    title_card_ptr->setPosn(136, 90);
    screenNav.getScreen(START_SCREEN)->addToUpdate(title_card_ptr);
    screenNav.getScreen(START_SCREEN)->addToUI(title_card_ptr);

    
    // BANNERS FOR START SCREEN
    Sprite* banner1 = spriteMap.getSprite(START_BANNER1);
    Sprite* banner2 = spriteMap.getSprite(START_BANNER2);
    Sprite* banner1_bkg = spriteMap.getSprite(BANNER1_BKG);
    Sprite* banner2_bkg = spriteMap.getSprite(BANNER2_BKG);
    
    banner1->setStateHandler(&idleStateHandler); // resume btn
    banner1->setState(SCROLLING_BANNER);
    banner1->setDir(LEFT);
    banner1->setPosn(0, 0);
    banner1->setFrameSpeed(0.5);
    screenNav.getScreen(START_SCREEN)->addToUpdate(banner1);
    
    banner1_bkg->setStateHandler(&idleStateHandler); // resume btn
    banner1_bkg->setState(IDLE);
    banner1_bkg->setDir(LEFT);
    banner1_bkg->setPosn(0, -10);
    
    banner2->setStateHandler(&idleStateHandler); // resume btn
    banner2->setState(SCROLLING_BANNER);
    banner2->setDir(LEFT);
    banner2->setPosn(0, 322);
    banner2->setFrameSpeed(0.5);
    // screenNav.getScreen(START_SCREEN)->addToUI(banner2);
    screenNav.getScreen(START_SCREEN)->addToUpdate(banner2);
    
    banner2_bkg->setStateHandler(&idleStateHandler); // resume btn
    banner2_bkg->setState(IDLE);
    banner2_bkg->setDir(LEFT);
    banner2_bkg->setPosn(0, 315);
    
    // creating level struct list
    
    CatcherLevelStruct levelOne = {0, 10, 30000, BETA_MATCHA};
    CatcherLevelStruct levelTwo = {0, 10, 20000, STRAWBERRY_MATCHA};
    CatcherLevelStruct levelThree = {0, 10, 10000, KOICHA};
    model.addLevel(levelOne);
    model.addLevel(levelTwo);
    model.addLevel(levelThree);
    
    // new buttons/textures
    Sprite* resume_game_btn = spriteMap.getSprite(RESUME_GAME_BTN);
    Sprite* go_to_next_lvl_btn = spriteMap.getSprite(NEXT_LVL_BTN);
    Sprite* try_again_btn = spriteMap.getSprite(TRY_AGAIN_BTN);
    Sprite* mini_how_to_play_box = spriteMap.getSprite(MINI_INSTR_BOX);
    Sprite* white_return_btn = spriteMap.getSprite(WHITE_RESUME_BTN);
    
    white_return_btn->setStateHandler(&returnButtonHandler); // resume btn
    white_return_btn->setState(NONE);
    white_return_btn->setDir(LEFT);
    white_return_btn->setPosn(-100, 0);
    screenNav.getScreen(START_SCREEN)->addToUI(white_return_btn);
    screenNav.getScreen(START_SCREEN)->addToUpdate(white_return_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(white_return_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(white_return_btn);
    
    resume_game_btn->setStateHandler(&navButtonHandler); // resume btn
    resume_game_btn->setState(NONE);
    resume_game_btn->setDir(LEFT);
    resume_game_btn->setPosn(269, 190.00);
    screenNav.getScreen(START_SCREEN)->addToUI(resume_game_btn);
    screenNav.getScreen(START_SCREEN)->addToUpdate(resume_game_btn);
    
    go_to_next_lvl_btn->setStateHandler(&replayButtonHandler); // resume btn
    go_to_next_lvl_btn->setState(NONE);
    go_to_next_lvl_btn->setDir(LEFT);
    go_to_next_lvl_btn->setPosn(495, 50);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(go_to_next_lvl_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(go_to_next_lvl_btn);
    
    try_again_btn->setStateHandler(&replayButtonHandler); // resume btn
    try_again_btn->setState(NONE);
    try_again_btn->setDir(LEFT);
    try_again_btn->setPosn(495, 50);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(try_again_btn);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(try_again_btn);
    
    mini_how_to_play_box->setStateHandler(&idleStateHandler); // resume btn
    mini_how_to_play_box->setState(NONE);
    mini_how_to_play_box->setDir(LEFT);
    mini_how_to_play_box->setPosn(0, 0);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUI(mini_how_to_play_box);
    screenNav.getScreen(GAMEPLAY_SCREEN)->addToUpdate(mini_how_to_play_box);
    
    resume_game_btn->setSheetMap(&sheetMap);
    go_to_next_lvl_btn->setSheetMap(&sheetMap);
    try_again_btn->setSheetMap(&sheetMap);
    mini_how_to_play_box->setSheetMap(&sheetMap);
    white_return_btn->setSheetMap(&sheetMap);
    
    // end
    
    //
    
    CatcherController controller = CatcherController(&model, &view);
    controller.setScreenNav(&screenNav);
    std::cout << "Instantiated MVC. (yay!) [main]\n";
    navButtonHandler.setGameController(&controller);
    idleStateHandler.setGameController(&controller);
    replayButtonHandler.setGameController(&controller);
    charStateHandler.setGameController(&controller);
    catcherStateHandler.setGameController(&controller);
    menuButtonHandler.setGameController(&controller);
    navButtonHandlerMenu.setGameController(&controller);
    returnButtonHandler.setGameController(&controller);
    exitButtonStateHandler.setGameController(&controller);
    instructionsButtonStateHandler.setGameController(&controller);
    instrBtnOnStartScrnStateHandler.setGameController(&controller);
    
    // begin gameplay
    model.setGamePlayTimer(controller.getGameplayTimer());
    controller.startGame();
    std::cout << "Game closed. [main]\n";
}
