cmake_minimum_required(VERSION 3.25)
project(Ryn.Native VERSION 0.1.0 LANGUAGES CXX)

set(Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/GLFW.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OpenGL.cpp
)

add_library(${PROJECT_NAME} SHARED ${Sources})
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

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Libraries/GLFW/${LIBRARY_DIRECTORY}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
