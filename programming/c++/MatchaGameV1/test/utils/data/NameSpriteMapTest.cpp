#include "catch.hpp"
#include <map>
#include <stdio.h>
#include <iostream>
#include "Sprite.hpp"
#include "NameSpriteMap.hpp"

// Test file for NameSpriteSheet map.

TEST_CASE( "NameSpriteMap is instantiated.", "[DB for sprites]" ) {
    
    // initialize
    SpriteSheet walkingSheet = SpriteSheet("winnie_walk_left.png",
                                        "winnie_walk_right.png",
                                        8,
                                        432.00,
                                        70.00);
    Sprite sprite(WINNIE);
    // empty map
    NameSpriteMap emptyMap;
    // map to add to
    NameSpriteMap addedToMap;
    addedToMap.addSprite(&sprite);

    SECTION( "Empty name-sprite map. Error for nonexistent key for name." ) {
        CHECK_THROWS(emptyMap.getSprite(PLEASANT_SKY));
        }

    SECTION( "Adding and accessing a sprite for a name-sprite map." ) {
        std::cout << "Adding a sprite to name-sprite map.\n";
        // orig sprite that was added
        REQUIRE( sprite.getName()        == WINNIE );
        REQUIRE( sprite.getState()       == NONE   );
        REQUIRE( sprite.getStateDir()    == LEFT   );
        REQUIRE( sprite.getFrameSpeed()  == 1      );
        REQUIRE( sprite.getPosn().getX() == 0      );
        REQUIRE( sprite.getPosn().getY() == 0      );

        // accessed sprite from map must have the same params
        Sprite* testSprite = addedToMap.getSprite(WINNIE);
        REQUIRE( testSprite->getName()        == WINNIE );
        REQUIRE( testSprite->getState()       == NONE   );
        REQUIRE( testSprite->getStateDir()    == LEFT   );
        REQUIRE( testSprite->getFrameSpeed()  == 1      );
        REQUIRE( testSprite->getPosn().getX() == 0      );
        REQUIRE( testSprite->getPosn().getY() == 0      );
    }

    SECTION( "Loading from JSON for name-sprite map." ) {
        std::cout << "Loading from JSON for name-sprite map.\n";
        REQUIRE( emptyMap.numSprites() == 0 );
        // json test file contains a name for winnie and pleasant_sky background
        emptyMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData.json");
        // check that there exists exactly two sprites with the correct NAME enums
        REQUIRE( emptyMap.numSprites() == 2 );
        REQUIRE( emptyMap.getSprite(WINNIE)       != nullptr );
        REQUIRE( emptyMap.getSprite(PLEASANT_SKY) != nullptr );

        // test Winnie sprite params
        Sprite* winnie = emptyMap.getSprite(WINNIE);
        REQUIRE( winnie->getName()        == WINNIE );
        REQUIRE( winnie->getState()       == NONE   );
        REQUIRE( winnie->getStateDir()    == LEFT   );
        REQUIRE( winnie->getFrameSpeed()  == 1      );
        REQUIRE( winnie->getPosn().getX() == 0      );
        REQUIRE( winnie->getPosn().getY() == 0      );

        // test sky sprite params
        Sprite* sky = emptyMap.getSprite(PLEASANT_SKY);
        REQUIRE( sky->getName()        == PLEASANT_SKY );
        REQUIRE( sky->getState()       == NONE         );
        REQUIRE( sky->getStateDir()    == LEFT         );
        REQUIRE( sky->getFrameSpeed()  == 1            );
        REQUIRE( sky->getPosn().getX() == 0            );
        REQUIRE( sky->getPosn().getY() == 0            );
    }

    SECTION( "Test that all sprites in sprite map point to the same sheet map." ) {
        std::cout << "Test that all sprites in sprite map point to the same sheet map.\n";
        REQUIRE( emptyMap.numSprites() == 0 );
        // json test file contains a name for winnie and pleasant_sky background
        emptyMap.loadJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/nameSpriteData.json");
        // check that there exists exactly two sprites with the correct NAME enums
        REQUIRE( emptyMap.numSprites() == 2 );
        REQUIRE( emptyMap.getSprite(WINNIE)       != nullptr );
        REQUIRE( emptyMap.getSprite(PLEASANT_SKY) != nullptr );

        // set sheet map for all sprites
        NameStateSheetMap sheetMap;
        sheetMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");

        emptyMap.setSheetMapAll(&sheetMap);

        // test sprites point to same map
        Sprite* winnie = emptyMap.getSprite(WINNIE);
        Sprite* sky = emptyMap.getSprite(PLEASANT_SKY);
        REQUIRE( sky->getSheetMap()    == &sheetMap );
        REQUIRE( winnie->getSheetMap() == &sheetMap );
    }
}
