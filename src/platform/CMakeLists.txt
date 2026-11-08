configure_file(ops_platform_config.h.in ops_platform_config.h @ONLY)
target_include_directories(openssl_provider_sdk_static PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}")
target_sources(openssl_provider_sdk_static PRIVATE "${OPS_PLATFORM}.c")
