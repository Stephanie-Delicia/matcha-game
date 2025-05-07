#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "ScreenModel.hpp"
#include "SCREEN.h"
#include "NameSpriteMap.hpp"
#include "NameStateSheetMap.hpp"

// Test file for a screen model.

TEST_CASE( "Creating a screen model.") {
    double eps = 0.00001; // within 0.001%
    ScreenModel emptyScreen = ScreenModel();
    ScreenModel testScreen = ScreenModel(640.00, 360.00);
    
    // instantiate a sprite sheet map and a sprite map
    NameSpriteMap spriteMap;
    spriteMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData.json");
    
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    
    // grab sprites we want for background and the player character
    Sprite* player_sprite = spriteMap.getSprite(WINNIE);
    Sprite* bg_sprite = spriteMap.getSprite(PLEASANT_SKY);
    
    // add new sprites
    testScreen.addToBG(bg_sprite);
    testScreen.addToMain(player_sprite);
    
    SECTION("Empty screen model a setting params.") {
        REQUIRE(emptyScreen.getMainQ().size()       == 0);
        REQUIRE(emptyScreen.getBackgroundQ().size() == 0);
        REQUIRE(emptyScreen.isActive()              == false);
        REQUIRE(emptyScreen.screenType()            == TEST_SCREEN);
        REQUIRE_THAT( emptyScreen.getWidth(),  Catch::WithinAbs(0.00, eps) );
        REQUIRE_THAT( emptyScreen.getHeight(), Catch::WithinAbs(0.00, eps) );
    }
    
    SECTION("Instantiate a screen with params.") {
        REQUIRE( testScreen.getMainQ().size()       == 1 );
        REQUIRE( testScreen.getBackgroundQ().size() == 1 );
        REQUIRE( testScreen.isActive()              == false );
        REQUIRE( testScreen.screenType()            == TEST_SCREEN );
        REQUIRE_THAT( testScreen.getWidth(),  Catch::WithinAbs(640.00, eps) );
        REQUIRE_THAT( testScreen.getHeight(), Catch::WithinAbs(360.00, eps) );
    }
    
    SECTION("Check if sprites are in the correct queues.") {
        REQUIRE(testScreen.onScreen(player_sprite));
        REQUIRE(testScreen.inBackground(bg_sprite));
    }
    
    SECTION("Activate and deactivate screen.") {
        REQUIRE(testScreen.isActive() == false);
        testScreen.activate();
        REQUIRE(testScreen.isActive());
        testScreen.deactivate();
        REQUIRE(testScreen.isActive() == false);
    }
    
    SECTION("Empty a screen and add and remove specific sprites.") {
        // check if sprites are present
        REQUIRE(testScreen.onScreen(player_sprite));
        REQUIRE(testScreen.inBackground(bg_sprite));
        // empty now
        testScreen.emptyScreen();
        REQUIRE(testScreen.onScreen(player_sprite) == false);
        REQUIRE(testScreen.onScreen(bg_sprite) == false);
        REQUIRE(testScreen.inBackground(player_sprite) == false);
        // add sprite again to screen
        testScreen.addToMain(player_sprite);
        REQUIRE(testScreen.onScreen(player_sprite));
        // remove background from background queue
        testScreen.removeBG(bg_sprite);
        testScreen.removeMain(player_sprite);
        REQUIRE(testScreen.onScreen(player_sprite) == false);
        REQUIRE(testScreen.inBackground(bg_sprite) == false);
    }
    
//    SECTION("Replace background and main queues.") {
//
//    }
    
//    SECTION("Create SDL surfaces.") {
//
//    }
}
