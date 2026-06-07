#include "mytest.hpp"
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

TEST_CASE("main.cpp test case 1") {
    CHECK(2 * 2 == 4), CHECK(true);
}

TEST_CASE("main.cpp test case 2") {
    CHECK(false), CHECK(2 * 2 == 5);
}

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    // To avoid warnings on VS for very naive implementations of CHECK.
    int val = 2 * 2;
    CHECK(val == 4);
    CHECK(val == 5);
    CHECK_MESSAGE(val == 4, "msg1");
    CHECK_MESSAGE(val == 5, "msg2");
}
