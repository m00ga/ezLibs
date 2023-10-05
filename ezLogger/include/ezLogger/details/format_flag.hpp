#pragma once

#include <ezLogger/details/common.hpp>
#include <ezLogger/details/log_message.hpp>

#include <memory>

namespace ezLogger {
namespace details {

class format_flag {
public:
  virtual ~format_flag() = default;
  virtual void format(const log_message &msg, dest_t &dest) = 0;
};

class custom_flag : public format_flag {
public:
  virtual std::unique_ptr<custom_flag> clone() = 0;
};
}; // namespace details
}; // namespace ezLogger
