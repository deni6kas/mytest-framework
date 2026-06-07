#include "mytest.hpp"

namespace other_namespace {
namespace {
void foo() {
    CHECK(2 * 2 == 7);
}
}  // namespace
}  // namespace other_namespace

namespace mytest_test3 {
namespace {
void case1() {
    if (true)  // NOLINT(readability-simplify-boolean-expr,readability-braces-around-statements)
        CHECK(2 * 2 == 5);
    else  // NOLINT(readability-braces-around-statements)
        CHECK(2 * 2 == 6);
    other_namespace::foo();
}
TEST_CASE_REGISTER(case1, "Test3.cpp test case with complex calls");
}  // namespace
}  // namespace mytest_test3
