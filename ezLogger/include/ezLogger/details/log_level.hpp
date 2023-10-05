#pragma once

#include <string_view>

namespace ezLogger {
namespace details {
enum class log_level { ERROR, INFO, WARN, DEBUG, TRACE };

static constexpr std::string_view level_to_string(log_level lvl) {
  switch (lvl) {
  case log_level::ERROR:
    return "ERROR";
  case log_level::INFO:
    return "INFO";
  case log_level::WARN:
    return "WARN";
  case log_level::DEBUG:
    return "DEBUG";
  case log_level::TRACE:
    return "TRACE";
  default:
    return "";
  }
}
}; // namespace details
}; // namespace ezLogger
