#!/bin/bash
set -euo pipefail

GCC_FLAGS="-std=c++20 -pedantic-errors -Wall -Wextra -Werror -g -o mytest_main"
if uname -a | grep -qE "Linux|Darwin"; then
    GCC_FLAGS+=" -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=address"
fi
for cmd in clang++-15 g++-12 clang++ g++; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" --version | grep "ubuntu" >/dev/null; then
        echo "$cmd $GCC_FLAGS"
        exit 0
    fi
done
for cmd in clang++; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" --version | grep "Apple" >/dev/null; then
        echo "$cmd $GCC_FLAGS"
        exit 0
    fi
done
for cmd in g++-12 g++; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" --version | grep "g++.* 12\." >/dev/null; then
        echo "$cmd $GCC_FLAGS"
        exit 0
    fi
done

CL_FLAGS="/std:c++20 /W4 /WX /EHsc /D_CRT_SECURE_NO_WARNINGS /Zi /RTC1 /MDd /Fe:mytest_main /nologo"
for cmd in cl; do
    if command -v "$cmd" >/dev/null 2>&1 && "$cmd" 2>&1 | grep "Microsoft (R) C/C++" >/dev/null; then
        echo "$cmd $CL_FLAGS"
        exit 0
    fi
done

echo "Unable to find suitable compiler" >&2
exit 1