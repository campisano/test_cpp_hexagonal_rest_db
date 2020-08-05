cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME yaml)
set(LIB_NAME libyaml-cpp.a)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    URL                     https://github.com/jbeder/yaml-cpp/archive/yaml-cpp-0.6.3.tar.gz
    URL_HASH                MD5=b45bf1089a382e81f6b661062c10d0c2
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/install
    CONFIGURE_COMMAND       ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_CXX_STANDARD=11
        -DYAML_CPP_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF
    BUILD_COMMAND           ${CMAKE_COMMAND} --build .
    INSTALL_COMMAND         ${CMAKE_COMMAND} --build . --target install
    )

externalproject_get_property(${NAME}_external INSTALL_DIR)
set(${NAME}_INCLUDE_DIRS ${INSTALL_DIR}/include CACHE STRING "")
set(${NAME}_LIBRARY_DIRS ${INSTALL_DIR}/lib CACHE STRING "")
set(${NAME}_LIBRARIES ${${NAME}_LIBRARY_DIRS}/${LIB_NAME} CACHE STRING "")
list(GET ${NAME}_LIBRARIES 0 TARGET_LOCATION)

set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM 1)
add_custom_target(${NAME}_clean_no_custom)
add_dependencies(${NAME}_clean_no_custom ${NAME}_external)

add_library(${NAME} STATIC IMPORTED GLOBAL)
set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${TARGET_LOCATION})
add_dependencies(${NAME} ${NAME}_clean_no_custom)
