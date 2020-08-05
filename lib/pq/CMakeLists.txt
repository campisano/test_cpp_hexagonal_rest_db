cmake_minimum_required(VERSION 3.3.2)

include(ExternalProject)

set(NAME pq)
set(LIB_NAME libpq.so.5)

externalproject_add(
    ${NAME}_external
    DOWNLOAD_DIR            ${CMAKE_CURRENT_SOURCE_DIR}/download
    URL                     https://ftp.postgresql.org/pub/source/v11.5/postgresql-11.5.tar.bz2
    URL_HASH                MD5=580da94f6d85046ff2a228785ab2cc89
    SOURCE_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    BINARY_DIR              ${CMAKE_CURRENT_BINARY_DIR}/build
    INSTALL_DIR             ${CMAKE_CURRENT_SOURCE_DIR}/install
    CONFIGURE_COMMAND       ./configure --quiet --prefix=<INSTALL_DIR> --without-readline --without-zlib
    BUILD_COMMAND           $(MAKE) MAKELEVEL=0 -C src/interfaces/libpq
    INSTALL_COMMAND         $(MAKE) MAKELEVEL=0 -C src/interfaces/libpq install
    COMMAND                 $(MAKE) MAKELEVEL=0 -C src/include install
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
add_dependencies(${NAME} ${NAME}_clean_no_custom)
