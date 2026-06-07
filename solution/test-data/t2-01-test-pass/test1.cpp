#include "mytest.hpp"

void case1() {
    CHECK(2 * 2 == 4);
}

TEST_CASE_REGISTER(case1, "Test1.cpp test case 1");

void case2() {
    CHECK(2 * 3 == 6);
}

TEST_CASE_REGISTER(case2, "Test1.cpp test case 2");
