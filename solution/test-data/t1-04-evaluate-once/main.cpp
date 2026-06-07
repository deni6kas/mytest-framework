#include <iostream>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include "mytest.hpp"

bool foo(bool x) {
    std::cerr << "evaluate\n";
    return x;
}

int main() {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    std::cerr << "1\n";
    CHECK(foo(true));
    std::cerr << "2\n";
    CHECK(foo(false));
    std::cerr << "3\n";
}
