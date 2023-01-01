#include <SDL3_image/SDL_image.h>
#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "Sprite.hpp"
#include "Posn.hpp"
#include "SpriteSheet.hpp"
#include "NameStateSheetMap.hpp"
#include <map>

// Test file for SpriteSheet class.

TEST_CASE( "All SpriteSheet parameters are consistent when instantiated.", "[SpriteSheet]" ) {
    // test examples
    float width = 432.00;
    float height = 70;
    int totalFrames = 8;
    float frameWidth = width / totalFrames;
    SpriteSheet testSheet = SpriteSheet("winnie_walk_left.png",  // left facing sheet
                                        "winnie_walk_right.png", // right facing sheet
                                        totalFrames,      // total frames
                                        width, // width
                                        height); // height
    
    SpriteSheet blankSheet = SpriteSheet(); // surfaces are null
    
    SECTION( "Creating a sprite sheet." ) {
        std::cout << "Create a sprite sheet.\n";
        REQUIRE( testSheet.getWidth()   == 432.00 );
        REQUIRE( testSheet.getHeight()  == 70.00 );
        REQUIRE( testSheet.getTotalFr() == 8 );
        REQUIRE( testSheet.getCurrFr()  == 0 );
        REQUIRE( testSheet.currX() == 0 );
        REQUIRE( testSheet.currY() == 70 );
    }
    
    SECTION( "Testing rectangle for frame from sprite sheet is correct." ) {
        SDL_FRect correctRect = {0, 70, frameWidth, 70};
        SDL_FRect resultRect = testSheet.getFrameRect();
        REQUIRE( resultRect.x == correctRect.x );
        REQUIRE( resultRect.y == correctRect.y );
        REQUIRE( resultRect.w == correctRect.w );
        REQUIRE( resultRect.h == correctRect.h );
    }
    
    SECTION( "Creating a blank sheet." ) {
        std::cout << "Create a blank sheet.\n";
        REQUIRE( blankSheet.getWidth()   == 0 );
        REQUIRE( blankSheet.getHeight()  == 0 );
        REQUIRE( blankSheet.getTotalFr() == 0 );
        REQUIRE( blankSheet.getCurrFr()  == 0 );
        REQUIRE( blankSheet.currX() == 0 );
        REQUIRE( blankSheet.currY() == 0 );
        
        // check for nullptrs for surfaces
        REQUIRE( blankSheet.getSrfcL() == nullptr );
        REQUIRE( blankSheet.getSrfcR() == nullptr );
    }
    
    SECTION( "Testing rectangle for frame from a BLANK sprite sheet is correct." ) {
        SDL_FRect correctRect = {0, 0, 0, 0};
        SDL_FRect resultRect = blankSheet.getFrameRect();
        REQUIRE( resultRect.x == correctRect.x );
        REQUIRE( resultRect.y == correctRect.y );
        REQUIRE( resultRect.w == correctRect.w );
        REQUIRE( resultRect.h == correctRect.h );
    }
    
    SECTION( "Setting the current frame number." ) {
        std::cout << "Setting the frame number.\n";
        
        testSheet.setFrameNum(2);
        blankSheet.setFrameNum(2);
        REQUIRE( testSheet.getCurrFr() == 2 );
        REQUIRE( blankSheet.getCurrFr() == 0 );
        
        testSheet.setFrameNum(-10);
        blankSheet.setFrameNum(-10);
        REQUIRE( testSheet.getCurrFr() == 6 );
        REQUIRE( blankSheet.getCurrFr() == 0 );
        
    }
}
