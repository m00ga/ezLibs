#pragma once

#include "ezLogger/details/log_level.hpp"
#include <ezLogger/default_formatter.hpp>
#include <ezLogger/details/format_flag.hpp>
#include <ezLogger/details/logger.hpp>
#include <ezLogger/details/str_hepler.hpp>
#include <ezLogger/registry.hpp>
#include <ezSocket/address_data.hpp>

#include <fmt/compile.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace ezNetwork {
namespace ezSocket {
struct socket_log_data {
  int sock_id;
  address_type sock_type;
};

struct socket_log_flag : public ezLogger::details::custom_flag {
  void format(const ezLogger::details::log_message &msg,
              ezLogger::details::dest_t &dest) override {
    int sock_id = 0;
    std::string_view sock_type = "NONE";
    if (!(msg.user_ctx_key == "-1" || msg.ctx == nullptr)) {
      auto data = msg.ctx->get<socket_log_data>(msg.user_ctx_key);
      if (data.get() != nullptr) {
        sock_id = data->sock_id;
        sock_type = addr_type_to_string(data->sock_type);
      }
    }

    auto fmt_msg = fmt::format(FMT_COMPILE("[{}:{}]"), sock_id, sock_type);

    ezLogger::details::str_helper::append_str(fmt_msg, dest);
  }
  std::unique_ptr<custom_flag> clone() override {
    return std::make_unique<socket_log_flag>();
  }
};

struct log_helper {
  using log_ptr = std::shared_ptr<ezLogger::details::logger>;

  inline static bool log_enabled = true;
  inline static std::string logger_name = "ezSocket";
  inline static void set_log_mode(bool mode) { log_enabled = mode; }
  inline static log_ptr init_logger() {
    if (!log_enabled) {
      return nullptr;
    }
    auto base_log = ezLogger::registry::instance().get("base");
    if (base_log == nullptr) {
      throw std::runtime_error("First make a base logger");
    }
    auto new_log = std::make_shared<ezLogger::details::logger>(
        logger_name, base_log->get_sinks());
    auto new_fmt = std::make_unique<ezLogger::default_formatter>();
    auto socket_flag = std::make_unique<socket_log_flag>();
    new_fmt->add_custom_flag('s', std::move(socket_flag));

    new_fmt->set_pattern("%s %+");
    new_log->set_formatter(std::move(new_fmt));
    ezLogger::registry::instance().register_logger(new_log);

    base_log->info("Succesfully created new logger with name {}", logger_name);

    return new_log;
  }

  inline static log_ptr get_logger() {
    if (log_enabled) {
      auto log = ezLogger::registry::instance().get(logger_name);
      if (log == nullptr) {
        log = init_logger();
      }
      return log;
    } else {
      return nullptr;
    }
  }

  template <typename... Args>
  inline static void log(ezLogger::details::log_level lvl,
                         std::string_view message, int sock_id,
                         Args &&...args) {
    log_ptr logger = get_logger();
    if (logger != nullptr) {
      logger->log<Args...>(lvl, message, std::forward<Args>(args)...,
                           std::to_string(sock_id));
    }
  }

  inline static void log(ezLogger::details::log_level lvl,
                         std::string_view message, int sock_id = -1) {
    log_ptr logger = get_logger();
    if (logger != nullptr) {
      logger->log(lvl, message, std::to_string(sock_id));
    }
  }

  inline static void add_to_ctx(int sock_id, address_type sock_type) {
    socket_log_data data{.sock_id = sock_id, .sock_type = sock_type};

    log_ptr logger = get_logger();
    if (logger != nullptr) {
      logger->add_to_context<socket_log_data>(std::to_string(sock_id),
                                              std::move(data));
    }
  }
};
}; // namespace ezSocket
}; // namespace ezNetwork
