cmake_minimum_required(VERSION 3.20)

pretty_print("Tests dir included")

set(TEST_EXECUTABLE_NAME string_test_runner)

file(
  GLOB_RECURSE BACKEND_SRCS
  LIST_DIRECTORIES TRUE
  CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/clevy_interpreter/clevy_stdlib/*.c)

set(TESTS_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strtold.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_to_upper.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_memmove.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_trim.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strcmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_insert.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strerror.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_sprintf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strcat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strpbrk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strspn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strncat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strtok.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strncmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strlen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strntollu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/string_test_runner.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_memcmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strchr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strrchr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_sscanf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strcspn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_memset.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_atoi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_to_lower.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strncpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strstr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_strcpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_memcpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/test_memchr.c)

add_executable(${TEST_EXECUTABLE_NAME} ${TESTS_SRCS})
add_dependencies(${TEST_EXECUTABLE_NAME} ${S21_STRING_LIB_NAME})

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

target_include_directories(${TEST_EXECUTABLE_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${TEST_EXECUTABLE_NAME} check PkgConfig::CHECK
                      ${S21_STRING_LIB_NAME})
