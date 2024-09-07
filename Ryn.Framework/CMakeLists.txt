add_library(RynFramework INTERFACE)
add_library(Ryn::Framework ALIAS RynFramework)

target_include_directories(RynFramework INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynFramework INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/InputContext.cpp
)
