cmake_minimum_required(VERSION 3.20)

set(S21_STRING_LIB_NAME S21_STRING)

set(STRING_LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strncpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_memset.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strrchr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strtok.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strspn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strntollu.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strerror.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sprintf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strcspn.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strstr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_sscanf.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_c_sharp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strchr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strcpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strlen.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_memchr.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strncmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strpbrk.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_memcmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strtold.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_memmove.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strcmp.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_atoi.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_memcpy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strncat.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/s21_strcat.c)

add_library(${S21_STRING_LIB_NAME} STATIC ${STRING_LIB_SRCS})

set_target_properties(
  ${S21_STRING_LIB_NAME}
  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Lib"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Bin")

# Rationale for interface: this target is static library, so it doesn't need any
# linker options. However, it's clients might need these opts
target_link_options(${S21_STRING_LIB_NAME} INTERFACE ${DEFAULT_LINKING_OPTIONS}
                    INTERFACE -lm)
target_compile_options(${S21_STRING_LIB_NAME} PUBLIC ${DEFAULT_COMPILE_OPTIONS})

target_include_directories(${S21_STRING_LIB_NAME}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/tests)
