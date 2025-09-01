cmake_minimum_required(VERSION 3.14)

project(names
    VERSION 0.1.0
    DESCRIPTION "Random name generator library and CLI tool"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#10.2.1")

# Configure version header
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/include/names/version.h.in"
    "${CMAKE_CURRENT_BINARY_DIR}/include/names/version.h"
    @ONLY
)

# Disable tests in Release builds to avoid Catch2 dependency
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    option(NAMES_BUILD_TESTS "Build tests" OFF)
else()
    option(NAMES_BUILD_TESTS "Build tests" ON)
endif()
option(NAMES_BUILD_CLI "Build CLI executable" ON)

add_subdirectory(src)

if(NAMES_BUILD_CLI)
    add_subdirectory(cli)
endif()

if(NAMES_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()