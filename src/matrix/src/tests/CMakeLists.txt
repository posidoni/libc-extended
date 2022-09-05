cmake_minimum_required(VERSION 3.20)

pretty_print("Matrix tests directory included!")

set(TEST_EXECUTABLE_NAME matrix_test_executable)

# If GSL is found, these variables are populated GSL_FOUND          - True if
# GSL found on the local system GSL_INCLUDE_DIRS   - Location of GSL header
# files. GSL_LIBRARIES      - The GSL libraries. GSL_VERSION        - The
# version of the discovered GSL install.
find_package(GSL REQUIRED)

set(TESTS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_mult_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_transpose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_determinant.c
    ${CMAKE_CURRENT_SOURCE_DIR}/matrix_test_runner.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_calc_complements.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_s21_inverse_matrix.c)

add_executable(${TEST_EXECUTABLE_NAME} ${TESTS_SRCS})
add_dependencies(${TEST_EXECUTABLE_NAME} ${S21_MATRIX_LIB_NAME})

set_target_properties(
  ${TEST_EXECUTABLE_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${TEST_EXECUTABLE_NAME} PRIVATE ${DEFAULT_LINKING_OPTIONS}
                    -lm)
target_compile_options(${TEST_EXECUTABLE_NAME}
                       PRIVATE ${DEFAULT_COMPILE_OPTIONS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED IMPORTED_TARGET check)

target_include_directories(
  ${TEST_EXECUTABLE_NAME}
  PRIVATE ${GSL_INCLUDE_DIRS}
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(${TEST_EXECUTABLE_NAME} check PkgConfig::CHECK
                      ${S21_MATRIX_LIB_NAME} ${GSL_LIBRARIES})
