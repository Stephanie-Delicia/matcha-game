#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "ScreenModel.hpp"

// Test file for a screen model.

TEST_CASE( "Creating a screen model.") {
    ScreenModel emptyScreen;
    ScreenModel testScreen = ScreenModel(640, 360);
    
    SECTION("Empty screen model a setting params.") {
        
    }
    
    SECTION("Instantiate a screen with params.") {

    }
    
    SECTION("Check if a sprite is on the main screen.") {

    }
    
    SECTION("Activate and deactivate screen.") {

    }
    
    SECTION("Empty a screen.") {

    }
    
    SECTION("Add and remove a sprite.") {

    }
    
    SECTION("Replace screen sprites.") {

    }
    
    SECTION("Replace background.") {

    }
    
    SECTION("Create SDL surfaces.") {

    }
    
}
