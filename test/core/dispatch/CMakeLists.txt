add_executable(ops_core_dispatch test_core_dispatch.c)
target_link_libraries(ops_core_dispatch PRIVATE
    openssl_provider_sdk_registry ops_build_options)
add_test(NAME core_dispatch COMMAND ops_core_dispatch)
set_tests_properties(core_dispatch PROPERTIES LABELS "core;unit")
