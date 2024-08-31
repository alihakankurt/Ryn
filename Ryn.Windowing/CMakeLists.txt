set(RYN_WINDOWING_SOURCES_FILES
    Source/Input/InputContext.cpp
)

if (RYN_PLATFORM_WINDOWS)
    list(APPEND RYN_WINDOWING_SOURCES_FILES
    )
elseif (RYN_PLATFORM_LINUX)
    list(APPEND RYN_WINDOWING_SOURCES_FILES
    )
elseif (RYN_PLATFORM_MACOS)
    list(APPEND RYN_WINDOWING_SOURCES_FILES
        Source/MacOS/CocoaWindow.mm
    )
endif()

add_library(RynWindowing ${RYN_WINDOWING_SOURCES_FILES})
add_library(Ryn::Windowing ALIAS RynWindowing)

target_include_directories(RynWindowing
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

target_link_libraries(RynWindowing
    PUBLIC
        Ryn::Core
    PRIVATE
        Ryn::CompilerOptions
)

if (RYN_PLATFORM_WINDOWS)
    target_link_libraries(RynWindowing
    )
elseif (RYN_PLATFORM_LINUX)
    target_link_libraries(RynWindowing
    )
elseif (RYN_PLATFORM_MACOS)
    target_link_libraries(RynWindowing
        PRIVATE
            "-framework Cocoa"
    )
endif()
