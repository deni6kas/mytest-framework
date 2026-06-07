#include "mytest.hpp"
#include <algorithm>
#include <iostream>
#include "mytest_internal.hpp"

namespace mytest {

// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
struct SubcaseState {
    int subcase_count = 0;
    int all_subcases = 0;
    int subcase_id = 0;
    std::string current_subcase_name;

    // NOLINTEND(misc-non-private-member-variables-in-classes)

    bool m_if_run_subcase(std::string_view name) {
        subcase_count++;
        if (subcase_count > all_subcases) {
            all_subcases++;
        }
        if (subcase_count == subcase_id) {
            current_subcase_name = std::string(name);
            return true;
        } else {
            return false;
        }
    }
};

SubcaseState &get_cur_state() {
    static SubcaseState cur_state;
    return cur_state;
}

// cppcheck-suppress unusedFunction
// cppcheck-suppress passedByValue
bool if_run_subcase(std::string_view name) {
    return get_cur_state().m_if_run_subcase(name);
}

std::vector<TestCase> &get_test_cases() {
    static std::vector<TestCase> tests;
    return tests;
}

bool &if_failed() {
    static bool failed = false;
    return failed;
}

// cppcheck-suppress unusedFunction
void check_case(
    bool failed,
    const char *expr_str,
    const char *file,
    int line,
    std::optional<std::string_view> msg
) {
    if (!failed) {
        return;
    }
    std::cerr << "CHECK(" << expr_str << ") at " << file << ":" << line
              << " failed!\n";
    if (msg) {
        std::cerr << "    message: " << *msg << '\n';
    }
    if (!(get_cur_state().current_subcase_name.empty())) {
        std::cerr << "    in subcase " << get_cur_state().current_subcase_name
                  << '\n';
    }
    if_failed() = true;
}

// cppcheck-suppress unusedFunction
void register_test_case(std::function<void()> test_case, const char *name) {
    get_test_cases().emplace_back(name, std::move(test_case));
}

int run_all_tests() {
    std::vector<TestCase> &tests = get_test_cases();
    std::sort(
        tests.begin(), tests.end(),
        [](const TestCase &a, const TestCase &b) { return a.m_name < b.m_name; }
    );

    int passed = 0;
    bool any_failed = false;
    SubcaseState &cur_subcase_state = get_cur_state();
    for (const auto &test_case : tests) {
        cur_subcase_state.all_subcases = 0;
        cur_subcase_state.subcase_id = 1;

        std::cerr << "Running \"" << test_case.m_name << "\"...\n";
        cur_subcase_state.current_subcase_name = {};

        while (true) {
            if_failed() = false;
            cur_subcase_state.subcase_count = 0;

            test_case.m_test_case();

            // cppcheck-suppress knownConditionTrueFalse
            if (if_failed()) {
                any_failed = true;
                break;
            }

            if (cur_subcase_state.subcase_id >=
                cur_subcase_state.all_subcases) {
                break;
            }

            std::cerr << "...another subcase...\n";
            cur_subcase_state.subcase_id++;
        }

        if (!if_failed()) {
            ++passed;
        }
    }

    std::cerr << "===== Tests passed: " << passed << "/" << tests.size()
              << " =====\n";

    if (any_failed) {
        return 1;
    } else {
        return 0;
    }
}

}  // namespace mytest
