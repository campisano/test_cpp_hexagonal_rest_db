cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME pqxx)
set(LIB_NAME libpqxx.so)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    URL                     https://github.com/jtv/libpqxx/archive/6.4.7.tar.gz
    URL_HASH                MD5=702afa5a6501948af391b895b8e446bc
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/install
    CONFIGURE_COMMAND       ${CMAKE_COMMAND} -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR> -DCMAKE_CXX_STANDARD=11
        -DSKIP_BUILD_TEST=YES
        -DPostgreSQL_INCLUDE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/../pq/install/include
        -DPostgreSQL_LIBRARY=${CMAKE_CURRENT_SOURCE_DIR}/../pq/install/lib
        -DPostgreSQL_TYPE_INCLUDE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/../pq/install/include/postgresql
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

add_library(${NAME} SHARED IMPORTED GLOBAL)
set_target_properties(${NAME} PROPERTIES IMPORTED_LOCATION ${TARGET_LOCATION})
add_dependencies(${NAME} pq ${NAME}_clean_no_custom)
