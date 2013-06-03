#!/bin/bash

sourceDirectory=$1

find . -iname "*.gcda" -print0 | xargs -0 rm -rf
./main/bin/testrunner
lcov --capture --directory "${sourceDirectory}" --output-file coverage.info --no-external
genhtml coverage.info --output-directory html
