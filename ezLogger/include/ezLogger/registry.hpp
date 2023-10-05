#pragma once

#include <ezLogger/details/logger.hpp>
#include <ezLogger/details/formatter.hpp>
#include <ezLogger/details/log_level.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace ezLogger {
class registry {
private:
  std::unordered_map<std::string, std::shared_ptr<details::logger>> _loggers;
  std::shared_ptr<details::logger> _default_logger;
  std::unique_ptr<details::formatter> _formatter;
  details::log_level _default_level{details::log_level::TRACE};
  std::mutex _registry_mutex;
  std::string _pattern;

  void register_logger_(const std::shared_ptr<details::logger> &new_logger);

  registry();
  ~registry() = default;

public:
  inline static registry &instance() {
    static registry _inst;
    return _inst;
  }

  details::log_level get_level() { return _default_level; }
  void set_level(details::log_level lvl) { _default_level = lvl; }
  void set_name(const std::string &name) { _default_logger->set_name(name); }

  void set_formatter(std::unique_ptr<details::formatter> &&formatter);
  void set_pattern(const std::string &pattern);
  void register_logger(const std::shared_ptr<details::logger> &new_logger);
  void set_default_logger(const std::shared_ptr<details::logger> &logger);
  std::shared_ptr<details::logger> default_logger();
  void initalize_logger(const std::shared_ptr<details::logger> &new_logger);
  std::shared_ptr<details::logger> get(const std::string &name);
};
}; // namespace ezLogger
