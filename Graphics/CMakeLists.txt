cmake_minimum_required(VERSION 3.25)
project(Ryn.Graphics VERSION 0.2.0 LANGUAGES CXX)

set(Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Renderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Buffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Shader.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OpenGL/OpenGLRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OpenGL/OpenGLBuffer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/OpenGL/OpenGLShader.cpp
)

add_library(${PROJECT_NAME} STATIC ${Sources})
target_link_libraries(${PROJECT_NAME} PUBLIC Ryn.Core Ryn.Mathematics Ryn.Collections Ryn.IO PRIVATE Ryn.Native CompileOptions)

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
        ${CMAKE_CURRENT_SOURCE_DIR}/Shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
)
