cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME json)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    DOWNLOAD_NO_EXTRACT     true
    URL                     https://github.com/nlohmann/json/releases/download/v3.7.0/json.hpp
    URL_HASH                MD5=3a33df05082ae70e663f19477c63b13e
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/install
    CONFIGURE_COMMAND       ""
    BUILD_COMMAND           ""
    INSTALL_COMMAND         ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/download/json.hpp <INSTALL_DIR>/include/json.hpp
    )

externalproject_get_property(${NAME}_external INSTALL_DIR)
set(${NAME}_INCLUDE_DIRS ${INSTALL_DIR}/include CACHE STRING "")

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
add_custom_target(${NAME}_clean_no_custom)
add_dependencies(${NAME}_clean_no_custom ${NAME}_external)

add_library(${NAME} INTERFACE)
add_dependencies(${NAME} ${NAME}_clean_no_custom)
