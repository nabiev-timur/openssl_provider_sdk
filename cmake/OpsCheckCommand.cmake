# CTest PASS_REGULAR_EXPRESSION ignores exit status. Require both here.
if(NOT DEFINED OPS_EXPECT_OUTPUT)
    message(FATAL_ERROR "OPS_EXPECT_OUTPUT is required")
endif()

set(ops_after_separator FALSE)
set(ops_command)
math(EXPR ops_last_arg "${CMAKE_ARGC} - 1")
foreach(ops_index RANGE 0 ${ops_last_arg})
    if(ops_after_separator)
        string(REPLACE ";" "\\;" ops_argument "${CMAKE_ARGV${ops_index}}")
        list(APPEND ops_command "${ops_argument}")
    elseif("${CMAKE_ARGV${ops_index}}" STREQUAL "--")
        set(ops_after_separator TRUE)
    endif()
endforeach()
if(NOT ops_command)
    message(FATAL_ERROR "Pass the command after --")
endif()

execute_process(COMMAND ${ops_command}
    RESULT_VARIABLE ops_result
    OUTPUT_VARIABLE ops_stdout
    ERROR_VARIABLE ops_stderr)
if(NOT "${ops_result}" STREQUAL "0")
    message(FATAL_ERROR
        "Command failed (${ops_result}): ${ops_command}\n${ops_stdout}\n${ops_stderr}")
endif()
if(NOT ops_stdout MATCHES "${OPS_EXPECT_OUTPUT}")
    message(FATAL_ERROR
        "Unexpected command output: ${ops_command}\n${ops_stdout}\n${ops_stderr}")
endif()
message(STATUS "${ops_stdout}")
