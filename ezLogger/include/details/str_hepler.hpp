#pragma once

#include "./details/common.hpp"
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>

namespace ezLogger {
namespace details {
template <typename T> struct str_helper_ {
public:
  inline static void append_str(std::string_view str, T &dest) {}
  inline static std::string get_str(const T &dest) {}
};
template <> struct str_helper_<std::string> {
public:
  static void append_str(std::string_view str, std::string &dest);
  static std::string get_str(const std::string &dest);
};

template <> struct str_helper_<std::ostringstream> {
public:
  static void append_str(std::string_view str, std::ostringstream &dest);
  static std::string get_str(const std::ostringstream &dest);
};

struct str_helper {
public:
  static void append_str(std::string_view str, dest_t &dest);
  template <typename T,
            typename std::enable_if_t<std::is_integral_v<T>, bool> = true>
  inline static void append_str(T value, dest_t &dest) {
    str_helper_<dest_t>::append_str(std::to_string(value), dest);
  }
  static std::string get_str(const dest_t &dest);
};
}; // namespace details
}; // namespace ezLogger
