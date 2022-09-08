cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME httplib)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    DOWNLOAD_NAME           ${NAME}.tar.gz
    URL                     https://github.com/yhirose/cpp-httplib/archive/refs/tags/v0.11.1.tar.gz
    URL_HASH                MD5=7e38ea1da92b44379c3475fab17c9a6d
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/source
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/install
    CONFIGURE_COMMAND       ""
    BUILD_COMMAND           ""
    INSTALL_COMMAND         ${CMAKE_COMMAND} -E copy <SOURCE_DIR>/httplib.h <INSTALL_DIR>/include/httplib.h
    )

externalproject_get_property(${NAME}_external INSTALL_DIR)
set(${NAME}_INCLUDE_DIRS ${INSTALL_DIR}/include CACHE STRING "")

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
add_custom_target(${NAME}_clean_no_custom)
add_dependencies(${NAME}_clean_no_custom ${NAME}_external)

add_library(${NAME} INTERFACE)
add_dependencies(${NAME} ${NAME}_clean_no_custom)
