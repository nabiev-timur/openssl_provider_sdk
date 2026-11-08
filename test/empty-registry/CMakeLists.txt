add_executable(ops_digest_empty test_digest_empty.c)
target_link_libraries(ops_digest_empty PRIVATE
    openssl_provider_sdk_registry ops_build_options)
add_test(NAME digest_empty COMMAND ops_digest_empty)

set_tests_properties(digest_empty PROPERTIES LABELS "registry")
