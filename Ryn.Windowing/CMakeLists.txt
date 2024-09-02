add_library(RynWindowing INTERFACE)
add_library(Ryn::Windowing ALIAS RynWindowing)

target_include_directories(RynWindowing INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include/Ryn DESTINATION ${CMAKE_INSTALL_PREFIX}/Include)

target_sources(RynWindowing INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Input/InputContext.cpp
    $<$<PLATFORM_ID:Darwin>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/MacOS/CocoaWindow.mm
    >
)
