cmake_minimum_required(VERSION 2.23)
project(libmenu)

option(LIBMENU_WITH_EXAMPLES "Compile examples" ON)

set(LIBRARY_HEADERS_DIR
        include/${PROJECT_NAME}
        )

set(LIBRARY_HEADERS
        ${LIBRARY_HEADERS_DIR}/menu.h
        )

set(LIBRARY_SOURCE_DIR
        src
        )

set(LIBRARY_SOURCES
        ${LIBRARY_SOURCE_DIR}/menu.cpp
        )

add_library(${PROJECT_NAME} STATIC ${LIBRARY_HEADERS} ${LIBRARY_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

if (LIBMENU_WITH_EXAMPLES)
    add_subdirectory(examples/based)
endif ()