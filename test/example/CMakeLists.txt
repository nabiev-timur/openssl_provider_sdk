# One consumer loads the aggregate demonstration provider.
add_executable(ops_example_test test_example.c)
target_link_libraries(ops_example_test PRIVATE OpenSSL::Crypto ops_build_options)
add_dependencies(ops_example_test ops_example)
add_test(NAME example_provider COMMAND ops_example_test $<TARGET_FILE_DIR:ops_example>)
set_tests_properties(example_provider PROPERTIES LABELS "example;provider;integration")

add_test(NAME openssl_example_list
    COMMAND "${CMAKE_COMMAND}"
        "-DOPS_EXPECT_OUTPUT=OPS-DUMMY-HASH.*ops_example"
        -P "${PROJECT_SOURCE_DIR}/cmake/OpsCheckCommand.cmake" --
        "${OPS_OPENSSL_EXECUTABLE}" list
        -provider-path $<TARGET_FILE_DIR:ops_example>
        -provider ops_example -propquery provider=ops-example -digest-algorithms)
set_tests_properties(openssl_example_list PROPERTIES
    LABELS "example;provider;integration;cli")

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/abc.txt" CONTENT "abc")
add_test(NAME openssl_example_digest
    COMMAND "${CMAKE_COMMAND}"
        "-DOPS_EXPECT_OUTPUT=00000126"
        -P "${PROJECT_SOURCE_DIR}/cmake/OpsCheckCommand.cmake" --
        "${OPS_OPENSSL_EXECUTABLE}" dgst
        -provider-path $<TARGET_FILE_DIR:ops_example>
        -provider ops_example -propquery provider=ops-example
        -OPS-DUMMY-HASH "${CMAKE_CURRENT_BINARY_DIR}/abc.txt")
set_tests_properties(openssl_example_digest PROPERTIES
    LABELS "example;provider;integration;cli")
