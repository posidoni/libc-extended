cmake_minimum_required(VERSION 3.20)

pretty_print("Build config module included")

set(CMAKE_BUILD_TYPE CACHE STRING "Debug")
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo")
if(NOT ENABLE_CXX_EXCEPTIONS)
  message(
    WARNING "Exceptions have been disabled. Any operation that would "
            "throw an exception will result in a call to std::abort() instead.")
endif()

set(DEFAULT_COMPILE_OPTIONS
    "-Wall;-Wextra;-pedantic"
    "$<$<CONFIG:Debug>:-O0>"
    "$<$<CONFIG:Debug,RelWithDebInfo>:-g>"
    "$<$<CONFIG:Release,RelWithDebInfo>:-O2;-march=native>"
    "$<$<BOOL:${ENABLE_CXX_EXCEPTIONS}>:-fno-exceptions>"
    "$<$<BOOL:${GENERATE_COVERAGE_ON}>:--coverage>"
    "$<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>"
    "$<$<COMPILE_LANGUAGE:CXX>:-std=c++20>"
    "$<$<COMPILE_LANGUAGE:C>:-std=c11>")

set(DEFAULT_LINKING_OPTIONS "$<$<BOOL:${GENERATE_COVERAGE_ON}>:--coverage>"
                            "$<$<BOOL:${ENABLE_ASAN}>:-fsanitize=address>")
