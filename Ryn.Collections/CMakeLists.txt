set(RYN_COLLECTIONS_SOURCE_FILES
    Source/Dummy.cpp
)

add_library(RynCollections ${RYN_COLLECTIONS_SOURCE_FILES})
add_library(Ryn::Collections ALIAS RynCollections)

target_include_directories(RynCollections
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
        $<INSTALL_INTERFACE:Include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Source>
)

target_link_libraries(RynCollections
    PUBLIC
        Ryn::Core
    PRIVATE
        Ryn::CompilerOptions
)
