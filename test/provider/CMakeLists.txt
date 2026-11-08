# Algorithm objects arrive through the fixture target; the SDK supplies entry.
add_library(test_provider MODULE)
set_target_properties(test_provider PROPERTIES PREFIX "" C_EXTENSIONS OFF)
target_link_libraries(test_provider PRIVATE
    openssl_provider_sdk_provider ops_test_algorithms ops_build_options)
