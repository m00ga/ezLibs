enable_testing()

add_executable(message_test log_message.cpp)
target_link_libraries(message_test PRIVATE ezLogger)

add_test(
    NAME log_message_test
    COMMAND $<TARGET_FILE:message_test>
)
