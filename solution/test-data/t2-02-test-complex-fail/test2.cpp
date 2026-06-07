#include "mytest.hpp"

void case1() {
    CHECK(2 * 2 == 4), CHECK(true);
}
TEST_CASE_REGISTER(case1, "Test2.cpp test case 1");

void case2() {
    CHECK(true), CHECK(2 * 2 == 5);
}
TEST_CASE_REGISTER(case2, "Test2.cpp test case 2");

void case3() {
    CHECK_MESSAGE(2 * 2 == 4, "test2-msg1");
    CHECK_MESSAGE(2 * 2 == 5, "test2-msg2");
    CHECK(true), CHECK(2 * 2 == 4);
    CHECK(2 * 2 == 5), CHECK(true);
}
TEST_CASE_REGISTER(case3, "Test2.cpp test case with multiple failures and messages");
