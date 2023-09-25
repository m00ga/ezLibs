#pragma once

#include "./details/format_flag.hpp"
#include <string>

namespace ezLogger {
namespace flags {

struct name_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct payload_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct level_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct Y_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct m_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct d_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct H_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct M_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct S_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

struct aggregate_flag : public details::format_flag {
private:
  std::string _str;

public:
  void format(const details::log_message &msg, details::dest_t &dest) override;

  void add_ch(char ch);
};

struct default_flag : public details::format_flag {
  void format(const details::log_message &msg, details::dest_t &dest) override;
};

}; // namespace flags
}; // namespace ezLogger
