add_library(openssl_provider_sdk_static STATIC
    ops_crt.c
    ops_algorithm.c
    ops_provider.c
    ops_provider_ctx.c
    ops_core.c
    ops_bio.c
    ops_params.c)
set_target_properties(openssl_provider_sdk_static PROPERTIES
    POSITION_INDEPENDENT_CODE ON C_EXTENSIONS OFF C_VISIBILITY_PRESET hidden)
target_compile_features(openssl_provider_sdk_static PUBLIC c_std_11)
target_include_directories(openssl_provider_sdk_static PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(openssl_provider_sdk_static
    PUBLIC OpenSSL::Crypto
    PRIVATE $<BUILD_INTERFACE:ops_build_options>)

add_subdirectory(platform)
