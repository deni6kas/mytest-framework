#pragma once

#include <functional>
#include <string>
#include <utility>
#include <vector>

namespace mytest {

struct TestCase {
    std::string m_name;                 // NOLINT
    std::function<void()> m_test_case;  // NOLINT

    TestCase(std::string name, std::function<void()> test_case)
        : m_name(std::move(name)), m_test_case(std::move(test_case)) {
    }
};

int run_all_tests();

}  // namespace mytest
