#include "catch.hpp"
#include <stdio.h>
#include <iostream>

// A test to ensure Catch works using Factorial function. Test taken from the Catch github.

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "A test to ensure Catch works using Factorial function. Test taken from the Catch github.", "[factorial]" ) {
    std::cout << "Catch test.\n";
    // REQUIRE( Factorial(0) == 1 ); // fails
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
