#include <iostream>
#include <string>
#include "mytest.hpp"

TEST_CASE("Subcase linear generated test") {
    std::cerr << "start\n";
    for (int i = 0; i < 3; i++) {
        std::cerr << "  i=" << i << "\n";
        SUBCASE("(a) i=" + std::to_string(i)) {
            std::cerr << "    a\n";
        }
        SUBCASE("(b) i=" + std::to_string(i)) {
            std::cerr << "    b\n";
        }
    }
    std::cerr << "end\n";
}
