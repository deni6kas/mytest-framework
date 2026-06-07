#include <iostream>
#include "mytest.hpp"

TEST_CASE("Subcase test") {
    std::cerr << "1";
    SUBCASE("a") {
        std::cerr << "2";
        CHECK(false);
        CHECK_MESSAGE(false, "msg1");
        SUBCASE("b") {
            std::cerr << "3";
        }
        CHECK(false);
        CHECK_MESSAGE(false, "msg2");
        SUBCASE("c") {
            std::cerr << "4";
        }
        std::cerr << "5";
    }
    std::cerr << "6";
    SUBCASE("d") {
        std::cerr << "7";
        SUBCASE("e") {
            std::cerr << "8";
        }
        SUBCASE("f") {
            std::cerr << "9";
        }
    }
    std::cerr << "end\n";
}
