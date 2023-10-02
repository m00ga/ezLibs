#pragma once

#include "details/formatter.hpp"
#include "details/log_message.hpp"

#include <memory>
#include <string>
namespace ezLogger {
namespace details {
class sink {
public:
  virtual ~sink() = default;
  virtual void log(const log_message &msg) = 0;
  virtual void set_pattern(const std::string &pattern) = 0;
  virtual void set_formatter(std::unique_ptr<formatter> &&fmt) = 0;
};
}; // namespace details
}; // namespace ezLogger
