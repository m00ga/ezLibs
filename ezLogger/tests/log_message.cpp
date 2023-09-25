#include "details/log_message.hpp"

#include <string>

const std::string test_name("test");
const std::string test_data("test_data");

int main() {
  ezLogger::details::log_message test_message(
      test_name, test_data, ezLogger::details::log_level::DEBUG);
  if (test_message.logger_name != test_name) {
    return 1;
  }
  if (test_message.payload != test_data) {
    return 1;
  }
  if (test_message.cachedTime.get() == nullptr) {
    return 1;
  }
  return 0;
}
