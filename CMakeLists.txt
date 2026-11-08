cmake_minimum_required(VERSION 3.24)
project(openssl_provider_sdk VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

find_package(OpenSSL 3.0 REQUIRED COMPONENTS Crypto)
include(CTest)
include(cmake/OpsBuildOptions.cmake)
include(cmake/OpsPlatform.cmake)
add_subdirectory(src)
include(cmake/OpsAlgorithms.cmake)
include(cmake/OpsProvider.cmake)

option(OPS_BUILD_EXAMPLES "Build the demonstration provider" ${PROJECT_IS_TOP_LEVEL})
if(OPS_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

if(BUILD_TESTING)
    add_subdirectory(test)
endif()
include(cmake/OpsInstall.cmake)
