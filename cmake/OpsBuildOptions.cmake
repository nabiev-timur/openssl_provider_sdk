# Project diagnostics stay private and are never exported to consumers.
option(OPS_WARNINGS_AS_ERRORS "Treat SDK and test warnings as errors" OFF)
add_library(ops_build_options INTERFACE)
target_compile_features(ops_build_options INTERFACE c_std_11)
target_compile_options(ops_build_options INTERFACE
    $<$<C_COMPILER_ID:GNU,Clang>:-Wall;-Wextra;-Wpedantic>
    $<$<C_COMPILER_ID:MSVC>:/W4>
    $<$<AND:$<BOOL:${OPS_WARNINGS_AS_ERRORS}>,$<C_COMPILER_ID:GNU,Clang>>:-Werror>
    $<$<AND:$<BOOL:${OPS_WARNINGS_AS_ERRORS}>,$<C_COMPILER_ID:MSVC>>:/WX>)
