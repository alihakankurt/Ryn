cmake_minimum_required(VERSION 3.25)
project(Ryn.Mathematics VERSION 0.2.0 LANGUAGES CXX)

set(Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Math.cpp
)

add_library(${PROJECT_NAME} STATIC ${Sources})
target_link_libraries(${PROJECT_NAME} PUBLIC Ryn.Core PRIVATE CompileOptions)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
    OUTPUT_NAME ${PROJECT_NAME}
)
