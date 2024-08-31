add_library(RynCompilerOptions INTERFACE)
add_library(Ryn::CompilerOptions ALIAS RynCompilerOptions)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    target_compile_options(RynCompilerOptions INTERFACE
        ## Warnings
        -Wall -Wextra # Enable all warnings

        -Wshadow # Warn whenever a local variable shadows another local variable
        -Wunused # Warn whenever a local variable is unused

        -Wcast-align # Warn whenever a cast changes the alignment of the pointer
        -Wold-style-cast # Warn for C-style casts

        -Wconversion # Warn for implicit conversions that may alter a value
        -Wsign-conversion # Warn for implicit conversions that may change the sign of an integer value

        -Wmissing-noreturn # Warn about functions which might be candidates for attribute noreturn
        -Wunreachable-code # Warn about code that will never be executed

        -Wformat=2 # Warn about string format arguments

        -Wno-unused-function # Disable warnings for unused functions
        -Wno-unused-parameter # Disable warnings for unused parameters

        ## Errors
        -Werror=nonnull # Error when a null pointer constant is passed to [[nonnull]] parameter

        -Werror=address # Error when a suspicious pointer usage is detected
        -Werror=init-self # Error when a variable is initialized with itself
        -Werror=uninitialized # Error when an uninitialized variable is used
        -Werror=pointer-arith # Error on pointer arithmetic for void and function pointers
        -Werror=write-strings # Error on writing to read-only memory

        -Werror=return-type # Error when a return type is mismatched

        -Werror=switch # Error on missing cases in switch statements
        -Werror=implicit-fallthrough # Error on implicit fallthrough in switch statements

        -Werror=missing-include-dirs # Error on missing include directories

        ## C++ specific
        -Werror=delete-non-virtual-dtor # Error on deleting a non-virtual destructor
        -Werror=missing-field-initializers # Error on missing field initializers
        -Werror=pessimizing-move # Error on pessimizing move operations

        ## No standard C++ libraries
        -nostdinc++
        -nostdlib++
        -fno-exceptions
        -fno-rtti

        ## Optimization
        $<$<CONFIG:Debug>:-O0 -g3 -ggdb3>
        $<$<CONFIG:Release>:-O3 -march=native>
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(RynCompilerOptions INTERFACE
        /W4 # Enable all warnings
        /Permissive- # Enable strict conformance mode
        /wd4201 # Disable warnings for nonstandard extension used: nameless struct/union
        /utf-8 # Set source and execution character set to UTF-8

        ## No standard C++ libraries
        /X
        /NODEFAULTLIB
        /EHs-
        /GR-

        /D_CRT_SECURE_NO_WARNINGS # Disable warnings for unsafe functions
        /D_CRT_SECURE_NO_WARNINGS_GLOBALS # Disable warnings for unsafe functions
        /D_CRT_NONSTDC_NO_WARNINGS # Disable warnings for non-ANSI functions
        /DWIN32_LEAN_AND_MEAN # Exclude rarely-used stuff from Windows headers

        ## Optimization
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2>
    )
else()
    message(FATAL_ERROR "Unsupported compiler")
endif()
