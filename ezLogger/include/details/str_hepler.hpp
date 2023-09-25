#pragma once

#include "./details/common.hpp"
#include <sstream>
#include <string>
#include <string_view>

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
  static std::string get_str(const dest_t &dest);
};
}; // namespace details
}; // namespace ezLogger
