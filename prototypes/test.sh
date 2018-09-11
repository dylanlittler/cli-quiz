#!/bin/bash

# This file pipes input to a program and checks the exit status,
# aborting if necessary. Output can be viewed on stdout as tests are run,
# to ensure that results match expectations.

# Ensure one command line argument has been provided
# with the name of the program to be tested

if [ $# -ne 1 ]
then
    echo "USAGE: test.sh [PROGRAM]"
    exit 1
fi

# Command line argument becomes the program to test
PROGRAM=$1

check_status() {
    EXIT_CODE = $1
    INPUT = $2
    if [ $EXIT_CODE -ne 0 ]
    then
	echo "fixed-width-input exited with failure."
	echo "Input was:"
	echo $INPUT
	exit 1
    fi
}

# Define variables with test inputs so that these can be passed to the program,
# and to the exit_status checker.

# Test for short input
TEST_ONE="This is some text"
TEST_TWO="This is some text that is designed to exceed the limit of 50 characters."
TEST_THREE="This is some text that is designed to exceed the limit of 100 characters with a lot of input text which just keeps going."
TEST_FOUR="This is a lot of input text, designed to test the program's ability to handle input that exceeds 150 characters. The output returned should wrap over 4 lines."
NO_SPACES_TEST="hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
NO_SPACES_LONG_TEST="hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh"
MEMORY_LIMIT_TEST="This input is designed to exceed the limit of the memory allocated for the program - currently 200 characters. A large amount of input will be provided to ensure that the program aborts safely. This input should be pasted while the program runs in Valgrind as well, to check for memory leaks."

# Simply add a variable to this loop to test other cases
for TEST_INPUT in {$TEST_ONE, $TEST_TWO, $TEST_THREE, $TEST_FOUR, $NO_SPACES_TEST, $NO_SPACES_LONG_TEST, $MEMORY_LIMIT_TEST}
do
    echo $TEST_INPUT | ./$PROGRAM
    check_status $? $TEST_INPUT
done

exit 0
