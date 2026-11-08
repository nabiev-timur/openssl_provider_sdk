add_executable(ops_params_test test_params.c)
target_link_libraries(ops_params_test PRIVATE
    openssl_provider_sdk_static ops_build_options)
add_test(NAME params COMMAND ops_params_test)
set_tests_properties(params PROPERTIES LABELS "params;unit")
