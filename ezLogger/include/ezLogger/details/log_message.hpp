#pragma once

#include <ctime>
#include <ezLogger/details/log_context.hpp>
#include <ezLogger/details/log_level.hpp>
#include <memory>
#include <string_view>
#include <string>

namespace ezLogger {
namespace details {
struct log_message {
  std::string_view logger_name;
  std::string_view payload;
  std::unique_ptr<std::tm> cachedTime;
  log_level level;
  std::shared_ptr<log_context> ctx;
  std::string user_ctx_key;

  log_message() = delete;
  log_message(std::string_view name, std::string_view message,
              details::log_level lvl,
              std::shared_ptr<log_context> context = nullptr)
      : logger_name(name), payload(message), level(lvl),
        cachedTime(new std::tm), ctx(context) {
    std::time_t raw;
    std::time(&raw);
    localtime_r(&raw, cachedTime.get());
  }
};
}; // namespace details
}; // namespace ezLogger
