#include <ezLogger/details/logger.hpp>
#include <ezLogger/default_formatter.hpp>
#include <mutex>

namespace ezLogger {
namespace details {
logger::logger(const std::string &name) : _name(name) {}
logger::logger(const std::string &name, sink_ptr &&sink) : _name(name) {
  _sinks.push_back(std::move(sink));
}

void logger::set_formatter(std::unique_ptr<details::formatter> formatter) {
  std::lock_guard<std::mutex> lock(_mutex);
  for (auto it = _sinks.begin(); it != _sinks.end(); ++it) {
    if (std::next(it) == _sinks.end()) {
      (*it)->set_formatter(std::move(formatter));
    } else {
      (*it)->set_formatter(formatter->clone());
    }
  }
}

void logger::set_pattern(const std::string &pattern) {
  std::lock_guard<std::mutex> lock(_mutex);
  auto new_formatter = std::make_unique<default_formatter>(pattern);
  set_formatter(std::move(new_formatter));
}

void logger::add_sink(sink_ptr &&sink) {
  std::lock_guard<std::mutex> lock(_mutex);
  _sinks.push_back(std::move(sink));
}
}; // namespace details
}; // namespace ezLogger
