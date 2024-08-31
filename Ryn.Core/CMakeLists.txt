set(RYN_CORE_SOURCE_FILES
    Source/String.cpp
    Source/Clock.cpp
)

if (RYN_PLATFORM_WINDOWS)
    list(APPEND RYN_CORE_SOURCE_FILES
    )
elseif (RYN_PLATFORM_LINUX)
    list(APPEND RYN_CORE_SOURCE_FILES
    )
elseif (RYN_PLATFORM_MACOS)
    list(APPEND RYN_CORE_SOURCE_FILES
        Source/MacOS/Clock.cpp
    )
endif()

add_library(RynCore ${RYN_CORE_SOURCE_FILES})
add_library(Ryn::Core ALIAS RynCore)

target_include_directories(RynCore
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

target_link_libraries(RynCore
    PUBLIC
    PRIVATE
        Ryn::CompilerOptions
)
