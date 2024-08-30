if(WIN32)
    set(RYN_PLATFORM_WINDOWS TRUE)
elseif(LINUX)
    set(RYN_PLATFORM_LINUX TRUE)
elseif(APPLE AND UNIX)
    set(RYN_PLATFORM_MACOS TRUE)
else()
    message(FATAL_ERROR "Unsupported platform")
endif()
