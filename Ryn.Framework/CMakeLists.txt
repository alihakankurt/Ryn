project(RynFramework)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Ryn::Framework ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

target_sources(${PROJECT_NAME} INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game.cpp
)

target_link_libraries(${PROJECT_NAME} INTERFACE
    Ryn::Core
    Ryn::Windowing
)
