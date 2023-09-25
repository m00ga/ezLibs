#include "details/log_message.hpp"
#include "./test_helper.hpp"
#include <string>

const std::string test_name("test");
const std::string test_data("test_data");

int main() {
  ezLogger::details::log_message test_message(
      test_name, test_data, ezLogger::details::log_level::DEBUG);
  TEST_ASSERT(test_message.logger_name == test_name);
  TEST_ASSERT(test_message.payload == test_data);
  TEST_ASSERT(test_message.cachedTime.get() != nullptr);
  return 0;
}
