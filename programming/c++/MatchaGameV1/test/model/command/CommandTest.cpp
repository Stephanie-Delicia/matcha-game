#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "Sprite.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"

// test file for command class for sprites. the command class specifically UPDATES
// the sprite, their position and current frame, given their state.

// commands extend from StateCommand class.

TEST_CASE( "Testing commands", "[commands]" ) {
    // setup
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    // sprite
    Sprite testSprite = Sprite(WINNIE, Posn(0, 0), LEFT, WALKING, &sheetMap);
    // commands
    WalkingCommand walkC;
    IdleCommand idleC;
    
    SECTION( "WalkingCommand" ) {
        std::cout << "Command tests.\n";
        // testing params
        REQUIRE( testSprite.getName()        == WINNIE         );
        REQUIRE( testSprite.getPosn().getX() == 0              );
        REQUIRE( testSprite.getPosn().getY() == 0              );
        REQUIRE( testSprite.getStateDir()    == LEFT           );
        REQUIRE( testSprite.getState()       == WALKING        );
        REQUIRE( testSprite.getFrameSpeed()  == 1              );
        REQUIRE( testSprite.getSheet(WALKING)->getCurrFr() == 0);
        // update sprite
        walkC.update(&testSprite);
        // test new posn
        REQUIRE( testSprite.getName()        == WINNIE         );
        REQUIRE( testSprite.getPosn().getX() == 1              ); // move one px right
        REQUIRE( testSprite.getPosn().getY() == 0              );
        REQUIRE( testSprite.getStateDir()    == LEFT           );
        REQUIRE( testSprite.getState()       == WALKING        );
        REQUIRE( testSprite.getFrameSpeed()  == 1              );
        // test new current frame number
        REQUIRE( testSprite.getSheet(WALKING)->getCurrFr() == 1);
        
    }
    
    SECTION( "IdleCommand" ) {
        // testing params
        REQUIRE( testSprite.getName()        == WINNIE      );
        REQUIRE( testSprite.getPosn().getX() == 0           );
        REQUIRE( testSprite.getPosn().getY() == 0           );
        REQUIRE( testSprite.getStateDir()    == LEFT        );
        REQUIRE( testSprite.getState()       == WALKING     );
        REQUIRE( testSprite.getFrameSpeed()  == 1           );
        REQUIRE( testSprite.getSheet(IDLE)->getCurrFr() == 0);
        // update sprite
        idleC.update(&testSprite);
        // all parameters should remain unchanged
        REQUIRE( testSprite.getName()        == WINNIE      );
        REQUIRE( testSprite.getPosn().getX() == 0           );
        REQUIRE( testSprite.getPosn().getY() == 0           );
        REQUIRE( testSprite.getStateDir()    == LEFT        );
        REQUIRE( testSprite.getState()       == WALKING     );
        REQUIRE( testSprite.getFrameSpeed()  == 1           );
        REQUIRE( testSprite.getSheet(IDLE)->getCurrFr() == 0);
    }
}
