cmake_minimum_required(VERSION 3.20)

pretty_print("Bigint subdirectory included")

set(S21_BIGINT_LIB_NAME S21_BIGINT)

set(S21_BIGINT_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rounding/s21_bank_rounding.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rounding/s21_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rounding/s21_truncate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rounding/s21_round.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rounding/s21_rounding_helpers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/conversion/s21_from_decimal_to_float.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/conversion/s21_from_decimal_to_int.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/conversion/s21_from_float_to_decimal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/conversion/s21_from_int_to_decimal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/conversion/s21_negate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_api/s21_core_bit_api.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_api/s21_binary_arithmetic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_api/s21_binary_exponent.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_api/s21_binary_shifts.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/binary_api/s21_binary_bool_logic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_greater.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_less_or_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_less.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_greater_or_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_not_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/comparison/s21_is_equal.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_mod.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_sub.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_normalize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_mul.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_add.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arithmetic/s21_integer_div.c)

add_library(${S21_BIGINT_LIB_NAME} STATIC ${S21_BIGINT_SRCS})

set_target_properties(
  ${S21_BIGINT_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${S21_BIGINT_LIB_NAME} INTERFACE ${DEFAULT_LINKING_OPTIONS}
                    INTERFACE -lm)
target_compile_options(${S21_BIGINT_LIB_NAME} PUBLIC ${DEFAULT_COMPILE_OPTIONS})

target_include_directories(${S21_BIGINT_LIB_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
