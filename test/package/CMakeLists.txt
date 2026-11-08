cmake_minimum_required(VERSION 3.24)
project(ops_installed_consumer LANGUAGES C)

# This is an independent consumer: never add_subdirectory the SDK source tree.
find_package(openssl_provider_sdk 1 CONFIG REQUIRED)
find_program(OPS_OPENSSL_EXECUTABLE NAMES openssl REQUIRED)
get_filename_component(ops_sdk_sources "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
enable_testing()

add_library(ops_example MODULE "${ops_sdk_sources}/example/digest/dummy_hash.c")
set_target_properties(ops_example PROPERTIES PREFIX "")
target_link_libraries(ops_example PRIVATE openssl_provider_sdk_provider)

add_library(ops_hooked_provider MODULE
    "${ops_sdk_sources}/test/lifecycle/provider/hooks.c"
    "${ops_sdk_sources}/test/fixtures/test_digest_alpha.c"
    "${ops_sdk_sources}/test/fixtures/test_digest_helpers.c")
set_target_properties(ops_hooked_provider PROPERTIES PREFIX "")
target_link_libraries(ops_hooked_provider PRIVATE openssl_provider_sdk_provider)

add_executable(package_lifecycle
    "${ops_sdk_sources}/test/lifecycle/live/test_lifecycle_live.c")
target_link_libraries(package_lifecycle PRIVATE openssl_provider_sdk_static)
add_dependencies(package_lifecycle ops_hooked_provider)
add_test(NAME package_lifecycle COMMAND package_lifecycle
    $<TARGET_FILE_DIR:ops_hooked_provider> ops_hooked_provider)

add_executable(package_example "${ops_sdk_sources}/test/example/test_example.c")
target_link_libraries(package_example PRIVATE OpenSSL::Crypto)
add_dependencies(package_example ops_example)
add_test(NAME package_example COMMAND package_example $<TARGET_FILE_DIR:ops_example>)

file(GENERATE OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/abc.txt" CONTENT "abc")
add_test(NAME package_cli
    COMMAND "${CMAKE_COMMAND}" "-DOPS_EXPECT_OUTPUT=00000126"
        -P "${ops_sdk_sources}/cmake/OpsCheckCommand.cmake" --
        "${OPS_OPENSSL_EXECUTABLE}" dgst
        -provider-path $<TARGET_FILE_DIR:ops_example>
        -provider ops_example -propquery provider=ops-example
        -OPS-DUMMY-HASH "${CMAKE_CURRENT_BINARY_DIR}/abc.txt")
set_tests_properties(package_lifecycle package_example package_cli PROPERTIES
    LABELS "package;integration")
