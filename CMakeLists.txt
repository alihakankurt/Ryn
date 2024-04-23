cmake_minimum_required(VERSION 3.25)
project(Ryn VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CompileOptions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformDefinitions.cmake)

add_subdirectory(Core)
add_subdirectory(Mathematics)
add_subdirectory(Collections)
add_subdirectory(Native)
add_subdirectory(IO)
add_subdirectory(Graphics)
add_subdirectory(Windowing)
add_subdirectory(Framework)
