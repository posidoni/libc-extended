cmake_minimum_required(VERSION 3.20)

pretty_print("Math tests dir included")

set(TEST_EXECUTABLE_NAME math_test_runner)

set(MATH_TESTS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_tan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_sin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_pow.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_acos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_fmod.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_sqrt.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_atan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_exp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_ceil.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_fabs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_cos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_abs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/math_test_runner.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_asin.c)

add_executable(${TEST_EXECUTABLE_NAME} ${MATH_TESTS_SRCS})
add_dependencies(${TEST_EXECUTABLE_NAME} ${S21_MATH_LIB_NAME})

set_target_properties(
  ${TEST_EXECUTABLE_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${TEST_EXECUTABLE_NAME} PRIVATE ${DEFAULT_LINKING_OPTIONS}
                    PRIVATE -lm)
target_compile_options(${TEST_EXECUTABLE_NAME}
                       PRIVATE ${DEFAULT_COMPILE_OPTIONS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED IMPORTED_TARGET check)

target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(${TEST_EXECUTABLE_NAME} check PkgConfig::CHECK
                      ${S21_MATH_LIB_NAME})
