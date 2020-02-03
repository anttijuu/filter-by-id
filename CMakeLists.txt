cmake_minimum_required(VERSION 3.12)
project(FilterDataById)
include(GNUInstallDirs)
set(APP_NAME filter)

add_executable(${APP_NAME} main.cpp )
set_target_properties(${APP_NAME} PROPERTIES CXX_STANDARD 17)

find_package(Doxygen)
if (DOXYGEN_FOUND)

   configure_file( ${CMAKE_CURRENT_SOURCE_DIR}/doxyconfig ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY)
   add_custom_target(doc
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating API documentation with Doxygen" VERBATIM
   )
endif(DOXYGEN_FOUND)
