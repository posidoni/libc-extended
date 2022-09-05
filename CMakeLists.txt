cmake_minimum_required(VERSION 3.20)

project(
  LIBC_EXTENDED
  VERSION 1.0
  LANGUAGES C CXX)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_GENERATOR CACHE STRING "Ninja")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(USE_FOLDERS ON)

option(GENERATE_TESTS "Generates unit tests build systems for every lib" OFF)
option(GENERATE_COVERAGE_ON "Generates test coverate report" OFF)
option(ENABLE_CXX_EXCEPTIONS "Enables C++ exceptions" OFF)
option(ENABLE_ASAN "Enables ASAN for all CMake targets & subdirectories" OFF)
option(ENABLE_DOCS_TARGET "Enables docs / dvi target" ON)

# @Warning! Better lint project manually. Build time with this is very slow
option(ENABLE_LINTING "Enables CPPCHECK, CLANG-TIDY, IWUU Linting" OFF)

include(utils)
include(programs)
include(docs)
include(build_config)
include(linters)
include(CTest)
include(coverage)

add_subdirectory(${CMAKE_SOURCE_DIR}/src/bigint)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/cpp_containers)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/math)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/string)
add_subdirectory(${CMAKE_SOURCE_DIR}/src/matrix)
