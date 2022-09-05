cmake_minimum_required(VERSION 3.20)

# See FIND GSL cmake module
# https://cmake.org/cmake/help/latest/module/FindGSL.html
pretty_print("Matrix lib directory included!")

set(S21_MATRIX_LIB_NAME S21_MATRIX)

set(MATRIX_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sub_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_mult_number.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_inverse_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_eq_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_transpose.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sum_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_helpers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_create_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_mult_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_remove_matrix.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_calc_complements.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_determinant.c)

add_library(${S21_MATRIX_LIB_NAME} STATIC ${MATRIX_LIB_SRCS})

set_target_properties(
  ${S21_MATRIX_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${S21_MATRIX_LIB_NAME} INTERFACE ${DEFAULT_LINKING_OPTIONS}
                    INTERFACE -lm)
target_compile_options(${S21_MATRIX_LIB_NAME} PUBLIC ${DEFAULT_COMPILE_OPTIONS})

target_include_directories(${S21_MATRIX_LIB_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
