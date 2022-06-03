#!/bin/bash
echo -e "-------------------------------------------------------------------------------\n"
echo -e "Style test\n"
cd ../src
# We are interested only in STDERR. STDOUT is redirected to NULL.
OUTPUT=$(make lint 2>&1 > /dev/null)
printf 'Style test output:\n %s\n' "$OUTPUT"

if [ -z "$OUTPUT" ]; then
    STYLE_TEST_RESULT=0
else
    STYLE_TEST_RESULT=-1
fi;
printf 'Style test result: %s\n' "$STYLE_TEST_RESULT"
echo -e "-------------------------------------------------------------------------------\n"

echo -e "-------------------------------------------------------------------------------\n"
echo -e "Build test\n"
make fclean 2>&1 > /dev/null
# We are interested only in STDERR. STDOUT is redirected to NULL.
OUTPUT=$(make all 2>&1 > /dev/null)
printf 'Build test output:\n %s\n' "$OUTPUT"

if [ -z "$OUTPUT" ]; then
    BUILD_TEST_OUTPUT=0
else
    BUILD_TEST_OUTPUT=-1
fi;
printf 'Build test result: %s\n' "$BUILD_TEST_OUTPUT"

echo -e "-------------------------------------------------------------------------------\n"
echo -e "Functional test\n"

# We are interested only in STDERR. STDOUT is redirected to NULL.
OUTPUT=$(./test 2>&1 > /dev/null)

printf 'Functional test output:\n %s\n' "$OUTPUT"

if [ -z "$OUTPUT" ]; then
    FUNCTIONAL_TEST_OUTPUT=0
else
    FUNCTIONAL_TEST_OUTPUT=-1
fi;
printf 'Functional test result: %s\n' "$FUNCTIONAL_TEST_OUTPUT"
echo -e "-------------------------------------------------------------------------------\n"

if [[ $FUNCTIONAL_TEST_OUTPUT -eq 0 && $BUILD_TEST_OUTPUT -eq 0 && $STYLE_TEST_RESULT -eq 0 ]]; then
    exit 0
else
    exit 1
fi;