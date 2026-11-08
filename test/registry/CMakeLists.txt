add_executable(ops_digest_registry test_digest_registry.c)
target_link_libraries(ops_digest_registry PRIVATE
    ops_test_algorithms ops_build_options)
add_test(NAME digest_registry COMMAND ops_digest_registry)

set_tests_properties(digest_registry PROPERTIES LABELS "registry")
