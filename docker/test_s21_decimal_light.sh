#!/bin/bash

echo -e "-------------------------------------------------------------------------------\n"
echo -e "Build test\n"
cd ../src
make fclean 2>&1 > /dev/null
make
# We are interested only in STDERR. STDOUT is redirected to NULL.
OUTPUT=$(find . -name "test")

if [ -z "$OUTPUT" ]; then
    BUILD_TEST_OUTPUT=1
else
    BUILD_TEST_OUTPUT=0
fi;
printf 'Build test result: %s\n' "$BUILD_TEST_OUTPUT"

exit $BUILD_TEST_OUTPUT