#!/bin/bash

EXECUTABLE="../src/perfect"
TIMEOUT_DURATION=10
SCORE=0
TOTAL_SCORE=0

test_err()
{
    local temp_output=''
    temp_output="$(mktemp)"

    timeout "$TIMEOUT_DURATION" bash -c "$EXECUTABLE > $temp_output 2>&1"

    diff -Zq "$temp_output" "./references/ref1" > /dev/null 2>&1
    return $?
}

test_single()
{
    local temp_output=''
    temp_output="$(mktemp)"

    timeout "$TIMEOUT_DURATION" xargs -a ./input/input2 -0 -I{} bash -c "$EXECUTABLE {} > $temp_output 2>&1"

    diff -Zq "$temp_output" "./references/ref2" > /dev/null 2>&1
    return $?
}

test_multiple()
{
    local temp_output=''
    temp_output="$(mktemp)"

    timeout "$TIMEOUT_DURATION" xargs -a ./input/input3 -0 -I{} bash -c "$EXECUTABLE {} > $temp_output 2>&1"

    diff -Zq "$temp_output" "./references/ref3" > /dev/null 2>&1
    return $?
}

test_edge()
{
    local temp_output=''
    temp_output="$(mktemp)"

    timeout "$TIMEOUT_DURATION" xargs -a ./input/input4 -0 -I{} bash -c "$EXECUTABLE {} > $temp_output 2>&1"

    diff -Zq "$temp_output" "./references/ref4" > /dev/null 2>&1
    return $?
}

setup()
{
    pushd ../src > /dev/null || exit 1
    make -s build
    popd > /dev/null || exit 1
}

cleanup()
{
    pushd ../src > /dev/null || exit 1
    make -s clean
    popd > /dev/null || exit 1
}

test_fun_array=(                        \
	test_err            "Name 1"    25  \
	test_single         "Name 2"    25  \
	test_multiple       "Name 3"    25  \
	test_edge           "Name 4"    25  \
)

run_test()
{
    test_index="$1"
    test_func_index=$((test_index * 3))
    description=${test_fun_array[$((test_func_index + 1))]}
    points=${test_fun_array[$((test_func_index + 2))]}
    TOTAL_SCORE=$((TOTAL_SCORE + points))

    echo -ne "Testing\t\t$description\t"
    if ${test_fun_array["$test_func_index"]} ; then
        SCORE=$((SCORE + points))
        echo "$points/$points"
        return 0
    else
        echo "0/$points"
        return 1
    fi
}

test_all()
{
    for i in $(seq 0 "$((${#test_fun_array[@]} / 3 - 1))") ; do
        run_test "$i"
    done

    echo -e "\nTotal: $SCORE/$TOTAL_SCORE"
}

setup
if [ -z "$1" ] ; then
    test_all
else
    run_test "$1"
    exit $?
fi
cleanup
