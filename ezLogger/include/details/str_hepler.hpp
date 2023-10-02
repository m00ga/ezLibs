#pragma once

#include "./details/common.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

namespace ezLogger {
namespace details {
struct str_helper {
public:
  static void append_str(std::string_view str, dest_t &dest);
  template <typename T,
            typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
  inline static void append_str(T value, dest_t &dest) {
    dest.append(std::to_string(value));
  }

  static std::string get_str(const dest_t &dest);
  static void append_eol(dest_t &dest);
};
}; // namespace details
}; // namespace ezLogger
