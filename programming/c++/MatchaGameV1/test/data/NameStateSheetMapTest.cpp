#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include <map>
#include "Sprite.hpp"
#include "NameStateSheetMap.hpp"

// Test file for NameStateSheet map.

TEST_CASE( "NameStateSheetMap is instantiated.", "[DB]" ) {
    
    // initialize
    SpriteSheet walkingSheet = SpriteSheet("winnie_walk_left.png",  // left facing sheet
                                        "winnie_walk_right.png", // right facing sheet
                                        8,      // total frames
                                        432.00, // width
                                        70.00); // height
    // empty map
    NameStateSheetMap emptyMap = NameStateSheetMap();
    // adding to map
    NameStateSheetMap testMap  = NameStateSheetMap();
    testMap.addSpriteSheet(WINNIE, WALKING, &walkingSheet);
    // map filled from json file
    NameStateSheetMap jsonMap  = NameStateSheetMap();

    SECTION( "Empty map. Error for nonexistent key for name." ) {
        std::cout << "Trying to access a non-existent sheet throws out of bounds error.\n";
        CHECK_THROWS(emptyMap.getSpriteSheet(WINNIE, WALKING));
        }
    
    SECTION( "Adding a sheet to map." ) {
        std::cout << "Adding a sheet to map.\n";
        // access sheet
        SpriteSheet* accessedSheet = testMap.getSpriteSheet(WINNIE, WALKING);
        
        // assert parameters are the same
        REQUIRE( accessedSheet->getWidth()   ==  walkingSheet.getWidth() );
        REQUIRE( accessedSheet->getHeight()  ==  walkingSheet.getHeight() );
        REQUIRE( accessedSheet->getTotalFr() ==  walkingSheet.getTotalFr() );
        REQUIRE( accessedSheet->getCurrFr()  ==  walkingSheet.getCurrFr() );
        REQUIRE( accessedSheet->currX()      ==  walkingSheet.currX() );
        REQUIRE( accessedSheet->currY()      ==  walkingSheet.currY() );
    }
    
    SECTION( "Updating an accessed sheet will update it in the map." ) {
        std::cout << "Updating an accessed sheet will update it in the map.\n";
        // access sheet
        SpriteSheet* accessedSheet = testMap.getSpriteSheet(WINNIE, WALKING);
        REQUIRE( accessedSheet->getCurrFr() ==  0 );
        REQUIRE( walkingSheet.getCurrFr()   ==  0 );
        
        // mutate sheet
        accessedSheet->setFrameNum(4);
        REQUIRE( accessedSheet->getCurrFr() ==  4 );
        
        // assert map sheet value changes after accessing the sheet and mutating it. the original sheet,
        // walkingSheet, should also be mutated since we've been working with its pointer within the map.
        accessedSheet = testMap.getSpriteSheet(WINNIE, WALKING);
        REQUIRE( walkingSheet.getCurrFr()   ==  4 );
        REQUIRE( accessedSheet->getCurrFr() ==  4 );
    }
    
    SECTION( "Reading in a JSON." ) {
        std::cout << "NameStateSheetMap reading in a JSON.\n";
        // map should initially be empty
        // CHECK_THROWS(jsonMap.getSpriteSheet(WINNIE, WALKING));
        
        // read from json file
        jsonMap.readJSON("/Users/stephaniemartinez/Downloads/matcha_game/matcha-game/programming/c++/MatchaGameV1/res/data/test/testSpriteSheetData.json");
        
        // check if sheet is present
//        SpriteSheet* accessedJSONSheet = jsonMap.getSpriteSheet(WINNIE, WALKING);
//        REQUIRE( accessedJSONSheet->getCurrFr() ==  0 );
//        
//        // mutate
//        accessedJSONSheet->setFrameNum(4);
//        REQUIRE( accessedJSONSheet->getCurrFr() ==  4 );
//        
//        // check if mutated in map as well
//        accessedJSONSheet = jsonMap.getSpriteSheet(WINNIE, WALKING);
//        REQUIRE( accessedJSONSheet->getCurrFr() ==  4 );
    }
}
