#!/bin/bash
set -euo pipefail
if [ "$#" -ge 1 ]; then
    COMMAND=("$@")
else
    # Default command to run each individual test, compiled.
    COMMAND=("./mytest_main")
fi
COMPILE_TIMEOUT=15s
TIMEOUT=15s  # Careful of Valgrind

if ! [ "${SIMPLE_COMPILATION_COMMAND+x}" ]; then
    SIMPLE_COMPILATION_COMMAND=$(./detect-compiler.sh)
fi
if [[ $SIMPLE_COMPILATION_COMMAND =~ "^cl " ]]; then
    SIMPLE_COMPILATION_COMMAND+=" /I../../"
else
    SIMPLE_COMPILATION_COMMAND+=" -I../../"
fi

echo "Compilation command: ${SIMPLE_COMPILATION_COMMAND[@]}"
echo "Run command: ${COMMAND[@]}"

FAIL=0
# Warning: use \033 instead of \e for compatibility with old Bash on macOS.

function test_ok {
    rm *.out &>/dev/null || true
    SOURCES="*.cpp mytest.cpp"
    if ! [ -f main.cpp ]; then
        SOURCES+=" mytest_main.cpp"
    fi
    # Sort after all TUs are listed so `mytest*` is in the middle
    SOURCES=$(echo $SOURCES | tr ' ' '\n' | sort | sed 's~^mytest~../../mytest~g')

    set +e
    # Prevent msys on Windows from converting Visual Studio's flags like /W4 to file paths
    # Redirect stderr to stdout so logs are not interleaved
    MSYS_NO_PATHCONV=1 MSYS2_ARG_CONV_EXCL="*" timeout -k 0.1s "$COMPILE_TIMEOUT" ${SIMPLE_COMPILATION_COMMAND[@]} $SOURCES 2>&1
    COMPILER_EXITCODE=$?
    set -e

    case "$COMPILER_EXITCODE" in
    0) ;;
    124)
        echo -e "\033[31;1mCE\033[0m: compilation timed out (or exit code $COMPILER_EXITCODE)"
        FAIL=1
        return 1
        ;;
    *)
        echo -e "\033[31;1mCE\033[0m"
        FAIL=1
        return 1
        ;;
    esac

    { timeout -k 0.1s "$TIMEOUT" "${COMMAND[@]}" 2>&3 | head -c 1000000 >stdout.out; echo ${PIPESTATUS[0]}>exit.out; } 3>&1 | head -c 1000000 >stderr.out
    if [[ $(cat exit.out) == "124" ]]; then
        echo -e "\033[31;1mTL\033[0m (or exit code $(cat exit.out))"
        FAIL=1
        return 1
    fi
    if {
            diff --unified --color=always /dev/null stdout.out &&
            diff --unified --color=always stderr.{sol,out} &&
            diff --unified --color=always -w exit.{sol,out}
        }; then
        echo PASS
        return 0
    else
        echo -e "\033[31;1mWA\033[0m (or wrong exit code)"
        FAIL=1
        return 0
    fi
}

for tn in $(cat tests.txt); do
    tn=$(echo $tn)  # To remove \r from tests.txt on Windows
    echo ===== $tn =====
    pushd test-data/$tn &>/dev/null
    if ! test_ok; then
        popd &>/dev/null
        break;
    else
        popd &>/dev/null
    fi
done
if [[ "$FAIL" == "0" ]]; then
    echo -e "===== \033[32;1mALL PASS\033[0m ====="
else
    echo -e "===== \033[31;1mSOME FAIL\033[0m ====="
fi
exit $FAIL
