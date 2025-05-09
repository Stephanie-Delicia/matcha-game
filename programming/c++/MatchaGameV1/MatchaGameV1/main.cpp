// main.cpp for running game
#include <stdio.h>
#include <iostream>
#include "NameStateSheetMap.hpp"
#include "NameSpriteMap.hpp"
#include "ScreenNavigator.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "GameView.hpp"
#include "GameModel.hpp"
#include "GameController.hpp"
/*
    From testing, I ensured that the model should have a navigator that
    has an active gameplay screen. This is what the controller should pass to
    the view to draw.
 
    Any type of input handling is handled by the player sprite, as well as updates.
    The controller gets to choose what gets handled/updated.
 
    In THIS game, the controller passes everything to a single player sprite which
    only interprets keyboard presses. The background should never change.
 */

int main(int argc, char* argv[]) {
    // load data
    // Sheet map
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    std::cout << "Loaded NameStateSheetMap (yay!). [main]\n";
//    // Sprite map
    NameSpriteMap spriteMap;
    spriteMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData.json");
    spriteMap.setSheetMapAll(&sheetMap);
    std::cout << "Loaded NameSpriteMap (yay!). [main]\n";
//    // Screen navigator
    ScreenNavigator screenNav = ScreenNavigator();
    screenNav.setNameSpriteMap(&spriteMap);
    // TODO: nav should through an error if you attemot loadJSON without setting SpriteMap.
    screenNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData.json");
    std::cout << "Loaded ScreenNavigator (yay!). [main]\n";
//    // ensure view, model, and controller are instantiated with everything they need.
    GameView view;
    GameModel model = GameModel(640, 360, "Move the sprite with keyboard arrow keys.");
    // load model with data
    model.setScreenNav(&screenNav);
    model.setNameToSheetMap(&sheetMap);
    model.setNameToSpriteMap(&spriteMap);
    // set main player
    // TODO: this setup should happen somewhere else... lol
    // ONLY THE MODEL KNOWS THIS INFORMATION! So either instantiate the model with this,
    // or have checks for the controller and ish, for ex. 
    Sprite* player = spriteMap.getSprite(WINNIE);
    Sprite* bg = spriteMap.getSprite(PLEASANT_SKY);
    player->setState(IDLE);
    player->setPosn(0, 267.00);
    model.setMainPlayer(player);
    bg->setState(IDLE);
    bg->setSheetMap(&sheetMap);
    bg->setPosn(0, 0);
    player->setSheetMap(&sheetMap);
    
    GameController controller = GameController(&model, &view);
    std::cout << "Instantiated MVC. [main]\n";
    // begin gameplay
    controller.startGame();
    std::cout << "Game closed. [main]\n";
}
