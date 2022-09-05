cmake_minimum_required(VERSION 3.20)

pretty_print("Coverage module included")

if(GENERATE_COVERAGE_ON)
  add_custom_target(
    GCOV_REPORT
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMAND echo "Generating code coverage report ..."
    COMMAND grcov . --branch --llvm -b Bin -t html -s ../../src -o Coverage
    COMMAND echo "Coverage reports generated"
    COMMAND echo "You can find them on : ${CMAKE_BINARY_DIR}/Coverage")
  # COMMAND open ${CMAKE_BINARY_DIR}/Coverage/*.html)
endif()
