cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

if ("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR
            "In-source builds are not permitted!\n"
            "Please use build_nox_visual.bat script to build solution!\n"
    )
endif()

include(cmake/macros.cmake)

project(nox LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE not specified, using Debug")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(NOX_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_library(nox STATIC "")
target_include_directories(nox
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(third_party)
create_project_source_tree(nox)

if (WIN32)
    target_compile_definitions(nox PRIVATE NOX_WIN32)
endif()
