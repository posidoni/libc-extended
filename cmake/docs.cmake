cmake_minimum_required(VERSION 3.20)

if(BUILD_DOCS_ON)
  pretty_print("Docs module included")

  find_program(DOXYGEN doxygen)

  set(DOXYGEN_DIR "${CMAKE_SOURCE_DIR}/docs")

  add_custom_target(
    dvi
    COMMENT "Generating Doxygen documentation"
    WORKING_DIRECTORY ${DOXYGEN_DIR}
    COMMAND ${DOXYGEN} Doxyfile)

  set_target_properties(dvi PROPERTIES ADDITIONAL_CLEAN_FILES
                                       ${DOXYGEN_DIR}/docs/documentation)
endif()
