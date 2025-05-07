#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "ScreenNavigator.hpp"
#include "ScreenModel.hpp"
#include "SCREEN.h"
#include "NameSpriteMap.hpp"
#include "NameStateSheetMap.hpp"

// Test file for a screen navigator.

TEST_CASE( "Creating a screen navigator.") {
    double eps = 0.00001; // within 0.001%
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
    
    // instantiate the navigators, bish.
    ScreenNavigator emptyNav = ScreenNavigator();
    ScreenNavigator testNav = ScreenNavigator();
    
    SECTION("Empty screen nav instantiation.") {
        // main screen was not assigned yet
        REQUIRE( emptyNav.getMainScreen() == nullptr );
        REQUIRE( emptyNav.getScreens().size() == 0 );
        REQUIRE( emptyNav.getScreens().size() == 0 );
        // check for other map sizes
    }
    
    SECTION("Set main screen.") {
        REQUIRE( testNav.getMainScreen() == nullptr );
        REQUIRE( testNav.getScreens().size() == 0 );
        REQUIRE( testNav.getScreens().size() == 0 );
        // set main screen
        testNav.setMainScreen(&testScreen);
        
        REQUIRE( testNav.getMainScreen()           == &testScreen );
        REQUIRE( testNav.getScreens().size()       == 1 );
        REQUIRE( testScreen.isActive()             == true );
        REQUIRE( testNav.isActive(&testScreen)     == true );
        REQUIRE( testNav.getScreens()[&testScreen] == true );
    }
    
    SECTION("Check if this nav has a given screen.") {
        // if the screen is not even in the map, you should catch an error
    }
    
    SECTION("Check if a given screen is active.") {
        REQUIRE( testNav.getMainScreen() == nullptr );
        REQUIRE( testNav.getScreens().size() == 0 );
        REQUIRE( testNav.getScreens().size() == 0 );
        
        testNav.addScreen(&testScreen);
        // if the screen is in the map, it should be inactive
        REQUIRE( testNav.isActive(&testScreen) == false );
        testNav.setMainScreen(&testScreen);
        REQUIRE( testNav.isActive(&testScreen) == true );
    }
    
    SECTION("Add screen.") {
        REQUIRE( testNav.getScreens().size() == 0 );
        // add
        testNav.addScreen(&testScreen);
        REQUIRE( testNav.getScreens().size()   == 1 );
        REQUIRE( testNav.isActive(&testScreen) == false );
        // set to main
        testNav.setMainScreen(&testScreen);
        REQUIRE( testNav.isActive(&testScreen) == true );
        
        // check that screen models are the same
        ScreenModel* accessedScreen = testNav.getMainScreen();
        REQUIRE( accessedScreen               == &testScreen );
        REQUIRE( accessedScreen->isActive()   == testScreen.isActive() );
        REQUIRE( accessedScreen->getWidth()   == testScreen.getWidth() );
        REQUIRE( accessedScreen->getHeight()  == testScreen.getHeight() );
        REQUIRE( accessedScreen->screenType() == testScreen.screenType() );
    }
    
    SECTION("Load data from JSON file.") {
        REQUIRE( testNav.getScreens().size() == 0 );
        REQUIRE( testNav.getMainScreen() == nullptr );
        // load JSON data
        testNav.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testScreenNavData.json");
        ScreenModel* activeScreen = testNav.getMainScreen();
        REQUIRE_THAT( activeScreen->getWidth(),  Catch::WithinAbs(640.00, eps) );
        REQUIRE_THAT( activeScreen->getHeight(),  Catch::WithinAbs(360.00, eps) );
        REQUIRE( activeScreen->isActive() == true );
    }
}

