#pragma once

#include <cstddef>
#include <initializer_list>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include <fmt/core.h>

#include <ezLogger/details/formatter.hpp>
#include <ezLogger/details/log_context.hpp>
#include <ezLogger/details/sink.hpp>

namespace ezLogger {
namespace details {
class logger {
public:
  using sink_ptr = std::unique_ptr<sink>;

  explicit logger(const std::string &name);
  logger(const std::string &name, sink_ptr &&sink);
  template <typename... Sinks>
  logger(const std::string &name, Sinks &&...sinks) : _name(name) {
    _sinks.reserve(sizeof...(sinks));
    (_sinks.push_back(std::forward<Sinks>(sinks)), ...);
  }
  logger(const std::string &name, std::vector<sink_ptr> &&sinks) : _name(name) {
    _sinks = std::move(sinks);
  }

  template <typename T, typename... Args>
  void add_to_context(const std::string &key, Args &&...args) {
    if (!_ctx) {
      _ctx = std::make_shared<details::log_context>();
    }
    _ctx->add<T>(key, std::forward<Args>(args)...);
  }

  std::shared_ptr<details::log_context> get_ctx() { return _ctx; }
  std::string name() { return _name; }
  void set_name(const std::string &name) { _name = name; }

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

  void add_sink(sink_ptr &&sink);

  std::vector<sink_ptr> get_sinks();

private:
  std::string _name;
  std::mutex _mutex;
  std::unique_ptr<formatter> _formatter;
  std::vector<sink_ptr> _sinks;
  std::shared_ptr<log_context> _ctx;
};
}; // namespace details
}; // namespace ezLogger
