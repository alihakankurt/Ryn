set(RYN_IO_SOURCE_FILES
)

if (RYN_PLATFORM_WINDOWS)
    list(APPEND RYN_IO_SOURCE_FILES
    )
elseif (RYN_PLATFORM_LINUX OR RYN_PLATFORM_MACOS)
    list(APPEND RYN_IO_SOURCE_FILES
        Source/Unix/File.cpp
    )
endif()

add_library(RynIO ${RYN_IO_SOURCE_FILES})
add_library(Ryn::IO ALIAS RynIO)

target_include_directories(RynIO
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

target_link_libraries(RynIO
    PUBLIC
        Ryn::Core
    PRIVATE
        Ryn::CompilerOptions
)
