#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include "./details/formatter.hpp"
#include "./details/log_context.hpp"
#include "./details/sink.hpp"

namespace ezLogger {
namespace details {
class logger {
public:
  using sink_ptr = std::unique_ptr<sink>;

  explicit logger(const std::string &name);
  logger(const std::string &name, sink_ptr &&sink);
  template <typename std::size_t N>
  logger(const std::string &name, sink_ptr (&&sinks)[N])
      : _name(name), _sinks(std::make_move_iterator(std::begin(sinks)),
                            std::make_move_iterator(std::end(sinks))) {}

  template <typename T, typename... Args>
  void add_to_context(const std::string &key, Args &&...args) {
    if (!_ctx) {
      _ctx = std::make_shared<details::log_context>();
    }
    _ctx->add<T>(key, std::forward<Args>(args)...);
  }

  std::shared_ptr<details::log_context> get_ctx() { return _ctx; }
  std::string name() { return _name; }

  template <typename... Args>
  void log(details::log_level level, std::string_view message, Args &&...args) {
    std::string fmt_string = fmt::format(message, std::forward<Args>(args)...);
    details::log_message msg(_name, fmt_string, level, _ctx);
    for (auto &sink : _sinks) {
      sink->log(msg);
    }
  }

  template <typename... Args>
  void info(std::string_view message, Args &&...args) {
    log(details::log_level::INFO, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void error(std::string_view message, Args &&...args) {
    log(details::log_level::ERROR, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void trace(std::string_view message, Args &&...args) {
    log(details::log_level::TRACE, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void debug(std::string_view message, Args &&...args) {
    log(details::log_level::DEBUG, message, std::forward<Args>(args)...);
  }

  template <typename... Args>
  void warn(std::string_view message, Args &&...args) {
    log(details::log_level::WARN, message, std::forward<Args>(args)...);
  }

  void set_formatter(std::unique_ptr<details::formatter> formatter);

  void set_pattern(const std::string &pattern);

private:
  std::string _name;
  std::mutex _mutex;
  std::unique_ptr<formatter> _formatter;
  std::vector<sink_ptr> _sinks;
  std::shared_ptr<log_context> _ctx;
};
}; // namespace details
}; // namespace ezLogger
