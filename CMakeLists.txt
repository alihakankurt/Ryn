cmake_minimum_required(VERSION 3.30)
project(Ryn VERSION 0.1.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Lib)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/CompilerOptions.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/BuildDefinitions.cmake)

add_subdirectory(Ryn.Core)
add_subdirectory(Ryn.Numerics)
add_subdirectory(Ryn.Collections)
add_subdirectory(Ryn.IO)
add_subdirectory(Ryn.Windowing)
add_subdirectory(Ryn.Framework)

add_library(${PROJECT_NAME})
add_library(Ryn::Ryn ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Ryn::Core
        Ryn::Numerics
        Ryn::Collections
        Ryn::IO
        Ryn::Windowing
        Ryn::Framework
    PUBLIC
        Ryn::BuildDefinitions
    PRIVATE
        Ryn::CompilerOptions
)

install(TARGETS ${PROJECT_NAME} EXPORT Ryn::Targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/Bin
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/Lib
)
