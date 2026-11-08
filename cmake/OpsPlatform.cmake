# Select one implementation for the SDK's private platform contract.
if(MSVC AND CMAKE_C_COMPILER_ID STREQUAL "MSVC")
    set(OPS_PLATFORM windows)
    set(OPS_PROVIDER_EXPORT "__declspec(dllexport)")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND
       CMAKE_C_COMPILER_ID MATCHES "^(GNU|Clang)$")
    set(OPS_PLATFORM linux)
    set(OPS_PROVIDER_EXPORT "__attribute__((visibility(\"default\")))")
else()
    message(FATAL_ERROR "SDK requires Linux GCC/Clang or Windows MSVC")
endif()

if(NOT CMAKE_SIZEOF_VOID_P MATCHES "^(4|8)$")
    message(FATAL_ERROR "SDK requires 32/64-bit targets")
endif()

set(OPS_COFF_SYMBOL_PREFIX "")
if(OPS_PLATFORM STREQUAL "windows" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(OPS_COFF_SYMBOL_PREFIX "_")
endif()
