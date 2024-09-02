set(RYN_FRAMEWORK_SOURCE_FILES
    Source/Game.cpp
)

add_library(RynFramework ${RYN_FRAMEWORK_SOURCE_FILES})
add_library(Ryn::Framework ALIAS RynFramework)

target_include_directories(RynFramework
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

target_link_libraries(RynFramework
    PUBLIC
        Ryn::Core
        Ryn::Collections
        Ryn::IO
        Ryn::Windowing
    PRIVATE
        Ryn::CompilerOptions
)
