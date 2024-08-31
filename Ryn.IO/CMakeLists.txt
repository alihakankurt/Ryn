project(RynIO)

add_library(${PROJECT_NAME} INTERFACE)
add_library(Ryn::IO ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

if (RYN_PLATFORM_MACOS OR RYN_PLATFORM_LINUX)
    target_sources(${PROJECT_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Unix/File.cpp
    )
endif()
