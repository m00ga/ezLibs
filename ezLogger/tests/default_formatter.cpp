#include "./default_formatter.hpp"
#include "./test_helper.hpp"
#include "details/common.hpp"
#include "details/str_hepler.hpp"

bool create_default_pattern() {
  ezLogger::default_formatter fmt;
  return true;
}

bool create_min_pattern() {
  ezLogger::default_formatter fmt("[%n:%l] %v");
  return true;
}

int main() {
  TEST_FUNCL("default_formatter::ctor", create_default_pattern);
  TEST_FUNCL("default_formatter::ctor", create_min_pattern);

  ezLogger::default_formatter fmt;
  ezLogger::details::log_message msg("test", "test_data",
                                     ezLogger::details::log_level::INFO);
  ezLogger::details::dest_t dest;
  fmt.format(msg, dest);
  TEST_ASSERTL("default_formatter::format",
               ezLogger::details::str_helper::get_str(dest) != "");

  fmt.set_pattern("[%n:%l] %v");
  TEST_ASSERTL("default_formatter::set_pattern", fmt.pattern() == "[%n:%l] %v");

  dest.clear();
  fmt.format(msg, dest);
  TEST_ASSERTL("default_formatter::format",
               ezLogger::details::str_helper::get_str(dest) ==
                   "[test:INFO] test_data\n");
  return 0;
}
