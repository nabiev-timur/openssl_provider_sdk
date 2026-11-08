add_subdirectory(digest)

# One demonstration provider collects the implementations from each class.
add_library(ops_example MODULE)
set_target_properties(ops_example PROPERTIES PREFIX "")
target_link_libraries(ops_example PRIVATE
    openssl_provider_sdk_provider ops_example_digest)
