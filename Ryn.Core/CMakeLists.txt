add_library(RynCore INTERFACE)
add_library(Ryn::Core ALIAS RynCore)

target_include_directories(RynCore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include/Ryn DESTINATION ${CMAKE_INSTALL_PREFIX}/Include)

target_sources(RynCore INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/String.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Clock.cpp
    $<$<PLATFORM_ID:Darwin>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/MacOS/Clock.cpp
    >
)
