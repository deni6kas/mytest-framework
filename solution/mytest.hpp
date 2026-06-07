#pragma once

#include <functional>
#include <optional>
#include <string_view>

namespace mytest {

void check_case(
    bool failed,
    const char *expr_str,
    const char *file,
    int line,
    std::optional<std::string_view> msg
);

void register_test_case(std::function<void()> test_case, const char *name);

bool if_run_subcase(std::string_view name);
}  // namespace mytest

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MYTEST_INTERNAL_CONCAT(a, b) a##b
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define MYTEST_INTERNAL_MAKE_NAME(a, b) MYTEST_INTERNAL_CONCAT(a, b)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define CHECK(expr) ::mytest::check_case(!(expr), #expr, __FILE__, __LINE__, {})

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define CHECK_MESSAGE(expr, msg) \
    ::mytest::check_case(!(expr), #expr, __FILE__, __LINE__, (msg))

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_CASE_REGISTER(fn, name)                                     \
    static const bool MYTEST_INTERNAL_MAKE_NAME(mytest_reg_, __LINE__) = \
        (::mytest::register_test_case((fn), (name)), true)

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define TEST_CASE(name)                                                  \
    static void MYTEST_INTERNAL_MAKE_NAME(mytest_case_, __LINE__)();     \
    static const bool MYTEST_INTERNAL_MAKE_NAME(mytest_reg_, __LINE__) = \
        (::mytest::register_test_case(                                   \
             MYTEST_INTERNAL_MAKE_NAME(mytest_case_, __LINE__), (name)   \
         ),                                                              \
         true);                                                          \
    static void MYTEST_INTERNAL_MAKE_NAME(mytest_case_, __LINE__)()

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define SUBCASE(name) if (::mytest::if_run_subcase(name))
