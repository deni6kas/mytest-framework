#include "mytest.hpp"
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

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
}
