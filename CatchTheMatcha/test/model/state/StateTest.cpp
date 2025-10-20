#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "Sprite.hpp"
#include "WalkingCommand.hpp"
#include "IdleCommand.hpp"
#include "CharacterState.hpp"

// test file for the state class for sprites. the state class handles both input and updates to the char
// based on its state.

TEST_CASE( "Testing states", "[state]" ) {
    // setup
    NameStateSheetMap sheetMap;
    sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
    // sprite
    Sprite testSprite = Sprite(WINNIE, Posn(0, 0), LEFT, WALKING, &sheetMap);
    // state for handling sprite updates and user input.
    CharacterState charState;
    
    SECTION( "Instantiating a CharState. Idle reading." ) {
        std::cout << "Instantiating a CharState. Idle reading.\n";
        // testing params
        REQUIRE( testSprite.getName()        == WINNIE         );
        REQUIRE( testSprite.getPosn().getX() == 0              );
        REQUIRE( testSprite.getPosn().getY() == 0              );
        REQUIRE( testSprite.getStateDir()    == LEFT           );
        REQUIRE( testSprite.getState()       == WALKING        );
        REQUIRE( testSprite.getFrameSpeed()  == 1              );
        REQUIRE( testSprite.getSheet(WALKING)->getCurrFr() == 0);
        // handle input for sprite, say that the user gives no key input, so the char should have an idle state now.
        SDL_Event idleEvent = { };
        idleEvent.type = SDL_EVENT_KEY_UP;
        charState.handleInput(&testSprite, idleEvent);
        REQUIRE( testSprite.getName()        == WINNIE      );
        REQUIRE( testSprite.getPosn().getX() == 0           );
        REQUIRE( testSprite.getPosn().getY() == 0           );
        REQUIRE( testSprite.getStateDir()    == LEFT        );
        REQUIRE( testSprite.getState()       == IDLE        );
        REQUIRE( testSprite.getFrameSpeed()  == 1           );
        REQUIRE( testSprite.getSheet(IDLE)->getCurrFr() == 0);
        // update sprite, since they are idle, there should be no changes to params.
        charState.update(&testSprite);
        REQUIRE( testSprite.getName()        == WINNIE      );
        REQUIRE( testSprite.getPosn().getX() == 0           );
        REQUIRE( testSprite.getPosn().getY() == 0           );
        REQUIRE( testSprite.getStateDir()    == LEFT        );
        REQUIRE( testSprite.getState()       == IDLE        );
        REQUIRE( testSprite.getFrameSpeed()  == 1           );
        REQUIRE( testSprite.getSheet(IDLE)->getCurrFr() == 0);

    }
    
    SECTION( "Instantiating a CharState. Walking reading." ) {
        std::cout << "Instantiating a CharState. Walking reading.\n";
        // NOTE: I would have liked to use charState's handleInput BUT
        // this thing requires real-time user input for grabbing keys.
        // I could make a mock class instead to directly insert keys instead
        // testing initial params
        REQUIRE( testSprite.getName()        == WINNIE         );
        REQUIRE( testSprite.getPosn().getX() == 0              );
        REQUIRE( testSprite.getPosn().getY() == 0              );
        REQUIRE( testSprite.getStateDir()    == LEFT           );
        REQUIRE( testSprite.getState()       == WALKING        );
        REQUIRE( testSprite.getFrameSpeed()  == 1              );
        REQUIRE( testSprite.getSheet(WALKING)->getCurrFr() == 0);
        // have char walking right now
        testSprite.setDir(RIGHT);
        testSprite.setFrameSpeed(2.00);
        charState.update(&testSprite);
        // check params
        REQUIRE( testSprite.getName()        == WINNIE         );
        REQUIRE( testSprite.getPosn().getX() == 2.00           );
        REQUIRE( testSprite.getPosn().getY() == 0              );
        REQUIRE( testSprite.getStateDir()    == RIGHT          );
        REQUIRE( testSprite.getState()       == WALKING        );
        REQUIRE( testSprite.getFrameSpeed()  == 2              );
        REQUIRE( testSprite.getSheet(WALKING)->getCurrFr() == 1);
        
    }
    
}
