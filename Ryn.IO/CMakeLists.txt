add_library(RynIO INTERFACE)
add_library(Ryn::IO ALIAS RynIO)

target_include_directories(RynIO INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynIO INTERFACE
    $<$<BOOL:${RYN_PLATFORM_MACOS}>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/POSIX/File.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/POSIX/Log.cpp
    >
)
