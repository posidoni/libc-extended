cmake_minimum_required(VERSION 3.20)

pretty_print("Math lib dir included")

set(S21_MATH_LIB_NAME S21_MATH)

set(MATH_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_atan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_fmod.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_fabs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_cos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_pow.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_exp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_abs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_floor.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_helpers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_acos.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_ceil.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_asin.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_tan.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_log.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sqrt.c)

add_library(${S21_MATH_LIB_NAME} STATIC ${MATH_LIB_SRCS})

set_target_properties(
  ${S21_MATH_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

target_link_options(${S21_MATH_LIB_NAME} INTERFACE ${DEFAULT_LINKING_OPTIONS})
target_compile_options(${S21_MATH_LIB_NAME} PUBLIC ${DEFAULT_COMPILE_OPTIONS})

target_include_directories(${S21_MATH_LIB_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/includes")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
