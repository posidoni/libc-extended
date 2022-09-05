cmake_minimum_required(VERSION 3.20)

pretty_print("BigInt lib tests dir included!")

set(TEST_EXECUTABLE_NAME bigint_test_runner)

set(BIGINT_TESTS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/rounding_tests/test_s21_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rounding_tests/test_s21_round.c
    ${CMAKE_CURRENT_SOURCE_DIR}/rounding_tests/test_s21_truncate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers/random_values.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers/int128_converters.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_helpers/printers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/conversion_tests/test_s21_from_decimal_to_float.c
    ${CMAKE_CURRENT_SOURCE_DIR}/conversion_tests/test_s21_negate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/conversion_tests/test_s21_from_decimal_to_int.c
    ${CMAKE_CURRENT_SOURCE_DIR}/conversion_tests/test_s21_from_float_to_decimal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/conversion_tests/test_s21_from_int_to_decimal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_tests/test_s21_div.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_tests/test_s21_sub.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_tests/test_s21_mul.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_tests/test_s21_mod.c
    ${CMAKE_CURRENT_SOURCE_DIR}/arithmetic_tests/test_s21_add.c
    ${CMAKE_CURRENT_SOURCE_DIR}/comparison_tests/test_s21_is_equal_not_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/comparison_tests/test_s21_is_less.c
    ${CMAKE_CURRENT_SOURCE_DIR}/comparison_tests/test_s21_is_less_or_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/comparison_tests/test_s21_is_greater.c
    ${CMAKE_CURRENT_SOURCE_DIR}/comparison_tests/test_s21_is_greater_or_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/bigint_test_runner.c)

add_executable(${TEST_EXECUTABLE_NAME} ${BIGINT_TESTS_SRCS})
add_dependencies(${TEST_EXECUTABLE_NAME} ${S21_BIGINT_LIB_NAME})

set_target_properties(
  ${TEST_EXECUTABLE_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${TEST_EXECUTABLE_NAME} PRIVATE ${DEFAULT_LINKING_OPTIONS})
target_compile_options(${TEST_EXECUTABLE_NAME}
                       PRIVATE ${DEFAULT_COMPILE_OPTIONS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED IMPORTED_TARGET check)

target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(${TEST_EXECUTABLE_NAME} check PkgConfig::CHECK
                      ${S21_BIGINT_LIB_NAME})
