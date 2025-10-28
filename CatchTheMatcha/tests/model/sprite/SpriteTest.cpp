#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "Sprite.hpp"
#include "NAME.h"
#include "DIRECTION.h"
#include "Posn.hpp"
#include "NameStateSheetMap.hpp"
#include "SpriteState.hpp"

// Test file for Sprite class. A Sprite represents a char.

/*
 TO TEST:
 getSheet
 updateSheet
 handleInput
 update
 drawSprite - can you test this?
 */

TEST_CASE( "All Sprite parameters are consistent when sprite is instantiated.", "[Sprite]" ) {
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");

    Sprite testSprite = Sprite(WINNIE, Posn(0, 0), LEFT, WALKING, &sheetMap);
    
    SECTION( "Create a sprite." ) {
        std::cout << "Create a sprite.\n";
        REQUIRE( testSprite.getName() == WINNIE );
        REQUIRE( testSprite.getPosn().getX() == 0 );
        REQUIRE( testSprite.getPosn().getY() == 0 );
        REQUIRE( testSprite.getStateDir() == LEFT );
        REQUIRE( testSprite.getState() == WALKING );
        REQUIRE( testSprite.getFrameSpeed() == 1 ); // default set to 1
        }
    
    SECTION( "Test Sprite setters." ) {
        std::cout << "Sprite Setters.\n";
        
        testSprite.setPosn(10, 15);
        REQUIRE( testSprite.getPosn().getX() == 10 );
        REQUIRE( testSprite.getPosn().getY() == 15 );
        
        testSprite.setState(IDLE);
        REQUIRE( testSprite.getState() == IDLE );
        
        testSprite.setDir(RIGHT);
        REQUIRE( testSprite.getStateDir() == RIGHT );
        
        testSprite.setFrameSpeed(2);
        REQUIRE( testSprite.getFrameSpeed() == 2 );
        }
}

