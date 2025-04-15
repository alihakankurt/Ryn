add_library(RynGraphics INTERFACE)
add_library(Ryn::Graphics ALIAS RynGraphics)

target_include_directories(RynGraphics INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<INSTALL_INTERFACE:Include>
)

find_package(Vulkan REQUIRED)

target_link_libraries(RynGraphics INTERFACE
    Vulkan::Vulkan
    $<$<BOOL:{RYN_PLATFORM_MACOS}>:
        "-framework Metal"
    >
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Include DESTINATION ${CMAKE_INSTALL_PREFIX})

target_sources(RynGraphics INTERFACE
    $<$<BOOL:{RYN_PLATFORM_MACOS}>:
        ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/Platform/VulkanMetal.mm
    >
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/Vulkan.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanInstance.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanInstance.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanDevice.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanDevice.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanSwapchain.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanSwapchain.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanRenderer.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Vulkan/VulkanRenderer.cpp
)
