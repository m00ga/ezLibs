#pragma once

#include <ezLogger/registry.hpp>
#include <ezLogger/details/formatter.hpp>
#include <ezLogger/details/log_level.hpp>
#include <ezLogger/details/logger.hpp>

#include <memory>
#include <string>
#include <string_view>
#include <utility>

namespace ezLogger {
template <typename... Args> void log(std::string_view message, Args &&...args) {
  details::log_level lvl = registry::instance().get_level();
  registry::instance().default_logger()->log(lvl, message,
                                             std::forward<Args>(args)...);
}

template <typename... Args>
void log(details::log_level lvl, std::string_view message, Args &&...args) {
  registry::instance().default_logger()->log(lvl, message,
                                             std::forward<Args>(args)...);
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
void warn(std::string_view message, Args &&...args) {
  log(details::log_level::WARN, message, std::forward<Args>(args)...);
}

template <typename... Args>
void debug(std::string_view message, Args &&...args) {
  log(details::log_level::DEBUG, message, std::forward<Args>(args)...);
}

template <typename... Args>
void trace(std::string_view message, Args &&...args) {
  log(details::log_level::TRACE, message, std::forward<Args>(args)...);
}

std::shared_ptr<details::logger> get(const std::string &name) {
  return registry::instance().get(name);
}

void set_default(const std::shared_ptr<details::logger> &logger) {
  registry::instance().set_default_logger(logger);
}

void set_formatter(std::unique_ptr<details::formatter> &&formatter) {
  registry::instance().set_formatter(std::move(formatter));
}

void set_pattern(const std::string &pattern) {
  registry::instance().set_pattern(pattern);
}

void set_name(const std::string &name) {
  registry::instance().set_name(name);
}
}; // namespace ezLogger
