#include <ezLogger/details/str_hepler.hpp>
#include <ezLogger/format_flags.hpp>

#include <fmt/compile.h>
#include <fmt/core.h>

namespace ezLogger {
namespace flags {
using ezLogger::details::str_helper;

void name_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.logger_name, dest);
}

void level_flag::format(const details::log_message &msg,
                        details::dest_t &dest) {
  str_helper::append_str(details::level_to_string(msg.level), dest);
}

void payload_flag::format(const details::log_message &msg,
                          details::dest_t &dest) {
  str_helper::append_str(msg.payload, dest);
}

void Y_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_year + 1900, dest);
}

void m_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_mon, dest);
}

void d_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_mday, dest);
}

void H_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_hour, dest);
}

void M_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_min, dest);
}

void S_flag::format(const details::log_message &msg, details::dest_t &dest) {
  str_helper::append_str(msg.cachedTime->tm_sec, dest);
}

void aggregate_flag::format(const details::log_message &msg,
                            details::dest_t &dest) {
  str_helper::append_str(_str, dest);
}

void aggregate_flag::add_ch(char ch) { _str += ch; }

void default_flag::format(const details::log_message &msg,
                          details::dest_t &dest) {
  auto fmt_msg = fmt::format(FMT_COMPILE("[{}-{}-{} {}:{}:{}] [{}:{}] {}"),
                             msg.cachedTime->tm_year + 1900,
                             msg.cachedTime->tm_mon, msg.cachedTime->tm_mday,
                             msg.cachedTime->tm_hour, msg.cachedTime->tm_min,
                             msg.cachedTime->tm_sec, msg.logger_name,
                             details::level_to_string(msg.level), msg.payload);
  str_helper::append_str(fmt_msg, dest);
}
}; // namespace flags
}; // namespace ezLogger
