#include "./registry.hpp"
#include "./default_formatter.hpp"
#include "./details/logger.hpp"
#include <memory>
#include <stdexcept>
namespace ezLogger {
registry::registry() {
  _formatter = std::make_unique<default_formatter>();
  _default_logger = std::make_shared<details::logger>("log");
}

void registry::register_logger_(
    const std::shared_ptr<details::logger> &new_logger) {
  std::string name = new_logger->name();
  if (_loggers.find(name) != _loggers.end()) {
    throw std::runtime_error("logger with name '" + name + "' already exists");
  }
  _loggers[name] = new_logger;
}
void registry::register_logger(
    const std::shared_ptr<details::logger> &new_logger) {
  std::lock_guard<std::mutex> lock(_registry_mutex);
  register_logger_(new_logger);
}

void registry::initalize_logger(
    const std::shared_ptr<details::logger> &new_logger) {
  std::lock_guard<std::mutex> lock(_registry_mutex);
  new_logger->set_formatter(_formatter->clone());
  register_logger_(new_logger);
}

std::shared_ptr<details::logger> registry::get(const std::string &name) {
  std::lock_guard<std::mutex> lock(_registry_mutex);
  auto found = _loggers.find(name);
  return found == _loggers.end() ? nullptr : found->second;
}

void registry::set_default_logger(
    const std::shared_ptr<details::logger> &logger) {
  std::lock_guard<std::mutex> lock(_registry_mutex);
  _default_logger = logger;
}

std::shared_ptr<details::logger> registry::default_logger() {
  return _default_logger;
}

void registry::set_formatter(std::unique_ptr<details::formatter> &&formatter) {
  _formatter = std::move(formatter);
}
void registry::set_pattern(const std::string &pattern) {
  _formatter = std::make_unique<default_formatter>(pattern);
}
}; // namespace ezLogger
