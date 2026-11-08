# A separate user archive is included explicitly to override the SDK defaults.
add_library(ops_user_hooks_archive STATIC)
target_link_libraries(ops_user_hooks_archive PRIVATE ops_user_hooks)

add_library(ops_archived_provider MODULE)
set_target_properties(ops_archived_provider PROPERTIES PREFIX "")
target_link_libraries(ops_archived_provider PRIVATE
    openssl_provider_sdk_provider ops_test_algorithms
    "$<LINK_LIBRARY:WHOLE_ARCHIVE,ops_user_hooks_archive>")
