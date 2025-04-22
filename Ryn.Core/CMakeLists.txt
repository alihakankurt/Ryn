add_library(RynCore INTERFACE)
add_library(Ryn::Core ALIAS RynCore)

target_include_directories(RynCore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynCore INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/String.cpp
    $<$<BOOL:${RYN_PLATFORM_MACOS}>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/POSIX/Memory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/POSIX/Process.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Mach/Clock.cpp
    >
)
