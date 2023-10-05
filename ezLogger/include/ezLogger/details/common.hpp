#pragma once

#include <string>
namespace ezLogger {
namespace details {
using dest_t = std::string;

struct null_mutex {
  void lock() {}
  void unlock() {}
};
}; // namespace details
}; // namespace ezLogger
