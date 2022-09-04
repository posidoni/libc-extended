cmake_minimum_required(VERSION 3.20)

if(ENABLE_LINTING)
  set(CMAKE_C_INCLUDE_WHAT_YOU_USE "include-what-you-use")
  set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use")
  set(CMAKE_C_CPPCHECK cppcheck --enable=all --suppress=missingIncludeSystem)
  set(CMAKE_CXX_CPPCHECK cppcheck --enable=all --suppress=missingIncludeSystem)
endif()
