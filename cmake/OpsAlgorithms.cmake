add_library(openssl_provider_sdk_registry INTERFACE)
target_link_libraries(openssl_provider_sdk_registry INTERFACE
    openssl_provider_sdk_static)
if(OPS_PLATFORM STREQUAL "windows")
    # Incremental linking adds padding; ICF must not merge records.
    target_link_options(openssl_provider_sdk_registry INTERFACE
        /INCREMENTAL:NO /OPT:NOICF)
else()
    math(EXPR OPS_ALGORITHM_SIZE "4 * ${CMAKE_SIZEOF_VOID_P}")
    set(ops_registry_script "${CMAKE_CURRENT_BINARY_DIR}/ops_digest_sections.ld")
    configure_file("${CMAKE_CURRENT_LIST_DIR}/ops_digest_sections.ld.in"
        "${ops_registry_script}" @ONLY)
    target_link_options(openssl_provider_sdk_registry INTERFACE
        "$<BUILD_INTERFACE:LINKER:-T,${ops_registry_script}>")
    set_property(TARGET openssl_provider_sdk_registry PROPERTY
        INTERFACE_LINK_DEPENDS "$<BUILD_INTERFACE:${ops_registry_script}>")
endif()
