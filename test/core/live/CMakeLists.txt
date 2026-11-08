add_executable(ops_core_live test_core_live.c)
target_link_libraries(ops_core_live PRIVATE
    openssl_provider_sdk_static ops_build_options)
add_dependencies(ops_core_live test_provider)
add_test(NAME core_live COMMAND ops_core_live $<TARGET_FILE_DIR:test_provider>)
set_tests_properties(core_live PROPERTIES LABELS "core;provider;integration")
