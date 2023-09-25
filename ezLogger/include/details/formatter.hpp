#pragma once

#include <memory>
#include <string>

#include "./common.hpp"
#include "./log_message.hpp"

namespace ezLogger {
namespace details {
class formatter {
public:
  virtual ~formatter() = default;
  virtual void format(const log_message &msg, dest_t &dest) = 0;
  virtual void set_pattern(const std::string &pattern) = 0;
  virtual std::unique_ptr<formatter> clone() = 0;
};
}; // namespace details
}; // namespace ezLogger
