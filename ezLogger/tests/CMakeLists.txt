enable_testing()

function(create_test test_name)
    add_executable(${test_name} ${test_name}.cpp)
    target_link_libraries(${test_name} PRIVATE ezLogger)

    add_test(
        NAME ${test_name}_test
        COMMAND $<TARGET_FILE:${test_name}>
    )
endfunction()

create_test(log_message)
create_test(str_helper)
create_test(format_flags)
create_test(default_formatter)
