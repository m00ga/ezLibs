#pragma once

#include "./log_level.hpp"
#include <ctime>
#include <memory>
#include <string_view>

namespace ezLogger {
namespace details {
struct log_message {
  std::string_view logger_name;
  std::string_view payload;
  std::unique_ptr<std::tm> cachedTime;
  log_level level;

  log_message() = delete;
  log_message(std::string_view name, std::string_view message,
              details::log_level lvl)
      : logger_name(name), payload(message), level(lvl),
        cachedTime(new std::tm) {
    std::time_t raw;
    std::time(&raw);
    localtime_r(&raw, cachedTime.get());
  }
};
}; // namespace details
}; // namespace ezLogger
