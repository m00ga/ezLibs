#pragma once

#include "./details/format_flag.hpp"
#include "./details/formatter.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace ezLogger {
class default_formatter : public details::formatter {
public:
  using custom_flags_map =
      std::unordered_map<char, std::unique_ptr<details::custom_flag>>;

  default_formatter();
  ~default_formatter() {}
  explicit default_formatter(const std::string &pattern);
  explicit default_formatter(std::string &&pattern);

  default_formatter(default_formatter &&fmt) = delete;
  default_formatter(const default_formatter &fmt) = delete;
  default_formatter &operator=(default_formatter &&fmt) = delete;

  void set_custom_flags(custom_flags_map &&flags);

  void format(const details::log_message &msg, details::dest_t &dest) override;
  void set_pattern(const std::string &pattern) override;

  const std::string pattern() const;
  std::unique_ptr<formatter> clone() override;

private:
  std::string _pattern;
  custom_flags_map _customFlags;
  std::vector<std::unique_ptr<details::format_flag>> _flags;

  void handleFlag(char flag);
  void compile_pattern(std::string_view pattern);
};
}; // namespace ezLogger
