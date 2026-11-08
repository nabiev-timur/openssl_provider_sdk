# The OpenSSL host intentionally does not link the SDK or algorithm fixtures.
add_executable(ops_digest_fetch test_digest_fetch.c)
target_link_libraries(ops_digest_fetch PRIVATE OpenSSL::Crypto ops_build_options)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Export a conflicting getter to exercise ELF interposition.
    set_target_properties(ops_digest_fetch PROPERTIES ENABLE_EXPORTS TRUE)
endif()
add_dependencies(ops_digest_fetch test_provider)
add_test(NAME digest_fetch COMMAND ops_digest_fetch $<TARGET_FILE_DIR:test_provider>)
set_tests_properties(digest_fetch PROPERTIES LABELS "provider;integration")
