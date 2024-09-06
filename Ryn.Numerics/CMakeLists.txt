add_library(RynNumerics INTERFACE)
add_library(Ryn::Numerics ALIAS RynNumerics)

target_include_directories(RynNumerics INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynNumerics INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Math.cpp
)
