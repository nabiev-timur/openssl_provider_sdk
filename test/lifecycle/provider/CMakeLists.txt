add_library(ops_user_hooks OBJECT hooks.c)
set_target_properties(ops_user_hooks PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(ops_user_hooks PRIVATE
    openssl_provider_sdk_static ops_build_options)

add_library(ops_hooked_provider MODULE)
set_target_properties(ops_hooked_provider PROPERTIES PREFIX "")
target_link_libraries(ops_hooked_provider PRIVATE
    openssl_provider_sdk_provider ops_test_algorithms ops_user_hooks)
