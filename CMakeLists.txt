cmake_minimum_required(VERSION 3.23)
project(libmenu
        VERSION 0.0.1
        DESCRIPTION "Menu creation library"
        LANGUAGES CXX)

option(LIBMENU_BUILD_TESTS "Build libmenu tests" OFF)
option(LIBMENU_BUILD_EXAMPLES "Build libmenu examples" ON)
option(LIBMENU_BUILD_DOCS "Build libmenu documentation" OFF)

add_library(${PROJECT_NAME})

set(LIBMENU_INCLUDES
        include/libmenu/Menu.hpp
        include/libmenu/MenuItem.hpp
        include/libmenu/MenuDrawer.hpp
        include/libmenu/MenuDrawerImpl.hpp
        )

set(LIBMENU_SOURCES
        ${LIBMENU_INCLUDES}
        src/MenuItem.cpp
        src/MenuDrawer.cpp
        src/MenuDrawerImpl.cpp
        )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${LIBMENU_SOURCES})

target_sources(${PROJECT_NAME} PRIVATE ${LIBMENU_SOURCES})

add_subdirectory(libs/fmt)

target_include_directories(${PROJECT_NAME} PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${PROJECT_NAME}>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}>
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )

if (LIBMENU_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif ()

if (LIBMENU_BUILD_EXAMPLES)
    add_subdirectory(examples/based_example)
endif ()

if (LIBMENU_BUILD_DOCS)
    include(cmake/doxygen.cmake)
endif ()