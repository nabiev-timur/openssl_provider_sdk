include(CMakePackageConfigHelpers)
set(ops_package_dir "lib/cmake/openssl_provider_sdk")
configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/openssl_provider_sdkConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/openssl_provider_sdkConfig.cmake"
    INSTALL_DESTINATION "${ops_package_dir}")
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/openssl_provider_sdkConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}" COMPATIBILITY SameMajorVersion)
install(TARGETS openssl_provider_sdk_static openssl_provider_sdk_registry
    openssl_provider_sdk_provider
    EXPORT openssl_provider_sdkTargets ARCHIVE DESTINATION lib)
install(EXPORT openssl_provider_sdkTargets
    FILE openssl_provider_sdkTargets.cmake DESTINATION "${ops_package_dir}")
install(FILES
    "${PROJECT_BINARY_DIR}/openssl_provider_sdkConfig.cmake"
    "${PROJECT_BINARY_DIR}/openssl_provider_sdkConfigVersion.cmake"
    DESTINATION "${ops_package_dir}")
install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/openssl_provider_sdk"
    DESTINATION include FILES_MATCHING PATTERN "*.h")
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    install(FILES "${ops_registry_script}" DESTINATION "${ops_package_dir}")
endif()
