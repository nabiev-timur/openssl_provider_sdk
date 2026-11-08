find_program(OPS_OPENSSL_EXECUTABLE NAMES openssl REQUIRED)

add_test(NAME openssl_list
    COMMAND "${CMAKE_COMMAND}"
        "-DOPS_EXPECT_OUTPUT=OPS-TEST-SHA256-A.*test_provider"
        -P "${PROJECT_SOURCE_DIR}/cmake/OpsCheckCommand.cmake" --
        "${OPS_OPENSSL_EXECUTABLE}" list
        -provider-path $<TARGET_FILE_DIR:test_provider>
        -provider test_provider -propquery provider=ops-test
        -digest-algorithms)
set_tests_properties(openssl_list PROPERTIES
    LABELS "provider;integration;cli")

# Exact bytes, no newline; expected SHA256 is a fixed known-answer vector.
file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/abc.txt" CONTENT "abc")
foreach(variant IN ITEMS A B)
    add_test(NAME openssl_digest_${variant}
        COMMAND "${CMAKE_COMMAND}"
            "-DOPS_EXPECT_OUTPUT=ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
            -P "${PROJECT_SOURCE_DIR}/cmake/OpsCheckCommand.cmake" --
            "${OPS_OPENSSL_EXECUTABLE}" dgst
            -provider-path $<TARGET_FILE_DIR:test_provider>
            -provider test_provider -propquery provider=ops-test
            -OPS-TEST-SHA256-${variant} "${CMAKE_CURRENT_BINARY_DIR}/abc.txt")
    set_tests_properties(openssl_digest_${variant} PROPERTIES
        LABELS "provider;integration;cli")
endforeach()
