#pragma once

#include <ezLogger/default_formatter.hpp>
#include <ezLogger/details/formatter.hpp>
#include <ezLogger/details/log_level.hpp>
#include <ezLogger/details/log_message.hpp>
#include <ezLogger/details/sink.hpp>

#include <memory>
#include <mutex>
#include <string>
#include <utility>

namespace ezLogger {
namespace sinks {
template <typename Mutex> class base_sink : public details::sink {
protected:
  std::unique_ptr<details::formatter> _formatter;
  Mutex _mutex;
  details::log_level _level{details::log_level::TRACE};

  virtual void sink_push(const details::log_message &msg) = 0;

  std::unique_ptr<details::sink> clone() override { return snk_clone(); }

  virtual std::unique_ptr<base_sink<Mutex>> snk_clone() = 0;

public:
  base_sink() : _formatter(std::make_unique<default_formatter>()) {}
  virtual ~base_sink() = default;

  details::log_level get_level() const { return _level; }

  void should_log(details::log_level level) override { _level = level; }

  void set_pattern(const std::string &pattern) override {
    std::lock_guard<Mutex> lock(_mutex);
    _formatter->set_pattern(pattern);
  }

  void set_formatter(std::unique_ptr<details::formatter> &&fmt) override {
    std::lock_guard<Mutex> lock(_mutex);
    _formatter.reset();
    _formatter = std::move(fmt);
  }

  void log(const details::log_message &msg) override {
    if (msg.level == _level || _level == details::log_level::TRACE) {
      std::lock_guard<Mutex> lock(_mutex);
      sink_push(msg);
    }
  }
};
}; // namespace sinks
}; // namespace ezLogger
