# Shared fixture objects are compiled once and delivered to both final targets.
add_library(ops_test_helpers OBJECT test_digest_helpers.c)
target_link_libraries(ops_test_helpers PRIVATE
    openssl_provider_sdk_static ops_build_options)
set_target_properties(ops_test_helpers PROPERTIES
    POSITION_INDEPENDENT_CODE ON C_EXTENSIONS OFF)

add_library(ops_test_alpha OBJECT test_digest_alpha.c)
target_link_libraries(ops_test_alpha PRIVATE
    openssl_provider_sdk_static ops_build_options)
set_target_properties(ops_test_alpha PROPERTIES
    POSITION_INDEPENDENT_CODE ON C_EXTENSIONS OFF)

# No external references: verifies inclusion of algorithm-only archive members.
add_library(ops_digest_beta STATIC test_digest_beta.c)
target_link_libraries(ops_digest_beta PRIVATE
    openssl_provider_sdk_static ops_build_options)
set_target_properties(ops_digest_beta PROPERTIES
    POSITION_INDEPENDENT_CODE ON C_EXTENSIONS OFF)

add_library(ops_test_algorithms INTERFACE)
target_sources(ops_test_algorithms INTERFACE
    $<TARGET_OBJECTS:ops_test_alpha>
    $<TARGET_OBJECTS:ops_test_helpers>)
target_link_libraries(ops_test_algorithms INTERFACE
    openssl_provider_sdk_registry
    "$<LINK_LIBRARY:WHOLE_ARCHIVE,ops_digest_beta>")
