add_executable(ops_lifecycle_live test_lifecycle_live.c)
target_link_libraries(ops_lifecycle_live PRIVATE
    openssl_provider_sdk_static ops_build_options)
add_dependencies(ops_lifecycle_live ops_hooked_provider ops_archived_provider)
add_test(NAME lifecycle_live COMMAND ops_lifecycle_live
    $<TARGET_FILE_DIR:ops_hooked_provider> ops_hooked_provider)
set_tests_properties(lifecycle_live PROPERTIES LABELS "provider;lifecycle;integration")

add_test(NAME lifecycle_archive COMMAND ops_lifecycle_live
    $<TARGET_FILE_DIR:ops_archived_provider> ops_archived_provider)
set_tests_properties(lifecycle_archive PROPERTIES LABELS "provider;lifecycle;integration")

add_test(NAME openssl_hooked_digest
    COMMAND "${CMAKE_COMMAND}"
        "-DOPS_EXPECT_OUTPUT=ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
        -P "${PROJECT_SOURCE_DIR}/cmake/OpsCheckCommand.cmake" --
        "${OPS_OPENSSL_EXECUTABLE}" dgst
        -provider-path $<TARGET_FILE_DIR:ops_hooked_provider>
        -provider ops_hooked_provider -propquery provider=ops-test
        -OPS-TEST-SHA256-A "${PROJECT_BINARY_DIR}/test/cli/abc.txt")
set_tests_properties(openssl_hooked_digest PROPERTIES
    LABELS "provider;lifecycle;integration;cli")
