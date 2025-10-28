#include "catch.hpp"
#include <stdio.h>
#include <iostream>
#include "Posn.hpp"

// Testing for Posn class. The posn class uses floats for x and y coordinates, so we'll compare using
// absolute difference.

TEST_CASE( "Creating a Posn.", "[posn]" ) {
    Posn testPosn = Posn(49.50, 80.72);
    Posn blankPosn = Posn();
    double eps = 0.00001; // within 0.001%
    
    SECTION("Creating a posn with x and y") {
        REQUIRE_THAT( testPosn.getX(), Catch::WithinAbs(49.50, eps) );
        REQUIRE_THAT( testPosn.getY(), Catch::WithinAbs(80.72, eps) );
    }
    
    SECTION("Creating a posn without x and y") {
        REQUIRE_THAT( blankPosn.getX(), Catch::WithinAbs(0, eps) );
        REQUIRE_THAT( blankPosn.getY(), Catch::WithinAbs(0, eps) );
    }
    
    SECTION("Setting x and y") {
        std::cout << "Posn tests.\n";
        testPosn.setX(0.09);
        testPosn.setY(-10.51);
        
        REQUIRE_THAT( testPosn.getX(), Catch::WithinAbs(0.09, eps) );
        REQUIRE_THAT( testPosn.getY(), Catch::WithinAbs(-10.51, eps) );
        
        blankPosn.setX(7.20);
        blankPosn.setY(88.88);
        
        REQUIRE_THAT( blankPosn.getX(), Catch::WithinAbs(7.20, eps) );
        REQUIRE_THAT( blankPosn.getY(), Catch::WithinAbs(88.88, eps) );
    }
}
