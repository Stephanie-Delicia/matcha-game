// main.cpp for running game
#include <stdio.h>
#include <iostream>
#include "NameStateSheetMap.hpp"
#include "NameSpriteMap.hpp"
#include "CharacterState.hpp"
#include "ScreenNavigator.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"
#include "CatcherGameModel.hpp"
#include "CatcherController.hpp"
/*
    In this latest update, we have a catcher game. The player must move the sprite around using
    key arrows.
 
    Additionally, I plan to add a start screen (not finalized design-wise) in which the player can click the
    "START" button to navigate to the gameplay screen.
 
    You can't go back after this lol
 */

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
    screenNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData.json");
    std::cout << "Loaded ScreenNavigator. [main]\n";
    
    // ensure view, model, and controller are instantiated with everything they need.
    GameView view;
    CatcherGameModel model = CatcherGameModel(640, 360, "Catch the matcha!");
    // load model with data
    model.setScreenNav(&screenNav);
    model.setNameToSheetMap(&sheetMap);
    model.setNameToSpriteMap(&spriteMap);
    
    // set main player and background
    CharacterState stateHandler = CharacterState();
    Sprite* player = spriteMap.getSprite(WINNIE);
    screenNav.getMainScreen()->addToUpdate(player);
    Sprite* bg = spriteMap.getSprite(PLEASANT_SKY);
    player->setStateHandler(&stateHandler);
    player->setState(IDLE);
    player->setPosn(0, 267.00);
    model.setMainPlayer(player);
    bg->setStateHandler(&stateHandler);
    bg->setState(IDLE);
    bg->setSheetMap(&sheetMap);
    bg->setPosn(0, 0);
    player->setSheetMap(&sheetMap);
    
    CatcherController controller = CatcherController(&model, &view);
    std::cout << "Instantiated MVC. (yay!) [main]\n";
    
    // begin gameplay
    controller.startGame();
    std::cout << "Game closed. [main]\n";
}

/*
 FOR JUST MOVING THE MAIN PLAYER AROUND:
 
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
 screenNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData.json");
 std::cout << "Loaded ScreenNavigator. [main]\n";
 
 // ensure view, model, and controller are instantiated with everything they need.
 GameView view;
 GameModel model = GameModel(640, 360, "Move the sprite with keyboard arrow keys.");
 
 // load model with data
 model.setScreenNav(&screenNav);
 model.setNameToSheetMap(&sheetMap);
 model.setNameToSpriteMap(&spriteMap);
 
 // set main player and background
 CharacterState stateHandler = CharacterState();
 Sprite* player = spriteMap.getSprite(WINNIE);
 screenNav.getMainScreen()->addToUpdate(player);
 Sprite* bg = spriteMap.getSprite(PLEASANT_SKY);
 player->setStateHandler(&stateHandler);
 player->setState(IDLE);
 player->setPosn(0, 267.00);
 model.setMainPlayer(player);
 bg->setStateHandler(&stateHandler);
 bg->setState(IDLE);
 bg->setSheetMap(&sheetMap);
 bg->setPosn(0, 0);
 player->setSheetMap(&sheetMap);
 
 GameController controller = GameController(&model, &view);
 std::cout << "Instantiated MVC. (yay!) [main]\n";
 
 // begin gameplay
 controller.startGame();
 std::cout << "Game closed. [main]\n";
 
 
 
 
 
 */
