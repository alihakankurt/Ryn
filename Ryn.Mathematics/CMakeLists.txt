add_library(RynMathematics INTERFACE)
add_library(Ryn::Mathematics ALIAS RynMathematics)

target_include_directories(RynMathematics INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynMathematics INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Math.cpp
)
