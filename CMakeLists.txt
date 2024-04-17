cmake_minimum_required(VERSION 3.25)
project(Ryn VERSION 0.1.0 LANGUAGES CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompileOptions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/GlobalSettings.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformDefinitions.cmake)

add_subdirectory(Core)
add_subdirectory(Mathematics)
add_subdirectory(Native)
add_subdirectory(Collections)
add_subdirectory(Windowing)
add_subdirectory(Rendering)
add_subdirectory(Framework)
