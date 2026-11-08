add_executable(ops_lifecycle_test test_lifecycle.c)
target_link_libraries(ops_lifecycle_test PRIVATE
    openssl_provider_sdk_registry ops_build_options)
add_test(NAME lifecycle COMMAND ops_lifecycle_test)
set_tests_properties(lifecycle PROPERTIES LABELS "provider;lifecycle;unit")
