add_library(RynWindowing INTERFACE)
add_library(Ryn::Windowing ALIAS RynWindowing)

target_include_directories(RynWindowing INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

target_link_libraries(RynWindowing INTERFACE
    $<$<PLATFORM_ID:Darwin>:
        "-framework Cocoa"
    >
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynWindowing INTERFACE
    $<$<PLATFORM_ID:Darwin>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaApplicationDelegate.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaApplicationDelegate.mm
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaWindowDelegate.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaWindowDelegate.mm
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaView.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaView.mm
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaWindow.hh
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Platform/Cocoa/CocoaWindow.mm
    >
)
