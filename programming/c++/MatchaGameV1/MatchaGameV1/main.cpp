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

int main(int argc, char* argv[]) {
    // view, model, and controller
    GameView view;
    GameModel model = GameModel(640, 360, "Move the sprite with keyboard arrow keys.");
    GameController controller = GameController(&model, &view);
    
    // load data
    // DATA LOADING PROCESS::
    // -> FIRST: load in the name state sheep map
    // -> SECOND: load in Sprites. These will really only have names as set params, with the rest like posn being set to
    // default values. For every sprite, set the map to the name state sheet map loaded in the first step.
    // -> THIRD: load in the screen navigator to be used. This uses sprites for a lot of stuff.
    
    // Step 1:
    NameStateSheetMap sheetMap;
    sheetMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    model.setNameToSheetMap(&sheetMap);
    
    // Step 2:
    NameSpriteMap spriteMap;
    spriteMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData");
    spriteMap.setSheetMapAll(&sheetMap);
    model.setNameToSpriteMap(&spriteMap);
    
    // Step 3:
    ScreenNavigator screenNav;
    screenNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData");
    model.setScreenNav(screenNav);
    
    // begin gameplay
    controller.startGame();
}


