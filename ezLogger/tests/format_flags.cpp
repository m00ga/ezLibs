#include "./format_flags.hpp"
#include "details/str_hepler.hpp"

#include <memory>
#include <string>

#include <fmt/compile.h>
#include <fmt/core.h>

#define TEST_FLAG(flag, msg, test_case)                                        \
  {                                                                            \
    ezLogger::details::dest_t dest;                                            \
    std::unique_ptr<flag> flg = std::make_unique<flag>();                      \
    flg->format(msg, dest);                                                    \
    if (!test_case(msg, dest))                                                 \
      return 1;                                                                \
  }

const std::string test_name("test");
const std::string test_data("test_data");

using namespace ezLogger::flags;
using ezLogger::details::dest_t;
using ezLogger::details::log_message;
using ezLogger::details::str_helper;

int main() {
  log_message test_msg(test_name, test_data,
                       ezLogger::details::log_level::INFO);

  TEST_FLAG(name_flag, test_msg,
            [](const log_message &msg, const dest_t &dest) {
              return str_helper::get_str(dest) == msg.logger_name;
            });

  TEST_FLAG(payload_flag, test_msg,
            [](const log_message &msg, const dest_t &dest) {
              return str_helper::get_str(dest) == msg.payload;
            });

  TEST_FLAG(level_flag, test_msg,
            [](const log_message &msg, const dest_t &dest) {
              return str_helper::get_str(dest) ==
                     ezLogger::details::level_to_string(msg.level);
            });

  TEST_FLAG(Y_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) ==
           std::to_string(msg.cachedTime->tm_year + 1900);
  });

  TEST_FLAG(m_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) == std::to_string(msg.cachedTime->tm_mon);
  });

  TEST_FLAG(d_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) == std::to_string(msg.cachedTime->tm_mday);
  });

  TEST_FLAG(H_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) == std::to_string(msg.cachedTime->tm_hour);
  });

  TEST_FLAG(M_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) == std::to_string(msg.cachedTime->tm_min);
  });

  TEST_FLAG(S_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
    return str_helper::get_str(dest) == std::to_string(msg.cachedTime->tm_sec);
  });

  TEST_FLAG(
      default_flag, test_msg, [](const log_message &msg, const dest_t &dest) {
        return str_helper::get_str(dest) ==
               fmt::format(FMT_COMPILE("[{}-{}-{} {}:{}:{}] [{}:{}] {}"),
                           msg.cachedTime->tm_year + 1900,
                           msg.cachedTime->tm_mon, msg.cachedTime->tm_mday,
                           msg.cachedTime->tm_hour, msg.cachedTime->tm_min,
                           msg.cachedTime->tm_sec, msg.logger_name,
                           ezLogger::details::level_to_string(msg.level),
                           msg.payload);
      });

  {
    std::unique_ptr<aggregate_flag> flg = std::make_unique<aggregate_flag>();
    flg->add_ch('[');
    flg->add_ch(']');
    dest_t dest;
    flg->format(test_msg, dest);

    if (str_helper::get_str(dest) != "[]") {
      return 1;
    }
  }

  return 0;
}
