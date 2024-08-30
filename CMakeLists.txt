cmake_minimum_required(VERSION 3.29)
project(Ryn VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/CompilerOptions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/PlatformDefinitions.cmake)

add_subdirectory(Ryn.Core)
add_subdirectory(Ryn.Windowing)
add_subdirectory(Ryn.Framework)

add_library(${PROJECT_NAME} STATIC)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Ryn::Core
        Ryn::Windowing
        Ryn::Framework
    PRIVATE
        RynCompilerOptions
)
