# OpenSSL resolves the entry point at runtime: force its archive member into
# the final module while retaining normal extraction for other SDK objects.
add_library(openssl_provider_sdk_provider INTERFACE)
target_link_libraries(openssl_provider_sdk_provider INTERFACE
    openssl_provider_sdk_registry)
if(OPS_PLATFORM STREQUAL "windows")
    if(CMAKE_SIZEOF_VOID_P EQUAL 4)
        target_link_options(openssl_provider_sdk_provider INTERFACE
            /INCLUDE:_OSSL_provider_init)
    else()
        target_link_options(openssl_provider_sdk_provider INTERFACE
            /INCLUDE:OSSL_provider_init)
    endif()
else()
    target_link_options(openssl_provider_sdk_provider INTERFACE
        LINKER:--require-defined=OSSL_provider_init)
endif()
