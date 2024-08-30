project(RynCore)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Ryn::Core ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

target_sources(${PROJECT_NAME} INTERFACE
)
