#include <iostream>
#include "mytest.hpp"

TEST_CASE("Subcase linear test") {
    std::cerr << "1";
    SUBCASE("a") {
        std::cerr << "2";
    }
    SUBCASE("b") {
        std::cerr << "3";
        CHECK(false);
    }
    SUBCASE("c") {
        std::cerr << "4";
    }
    std::cerr << "5\n";
}
