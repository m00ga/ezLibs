#pragma once

#include <fmt/core.h>

#include <memory>
#include <string>

#include <ezLogger/details/log_message.hpp>
#include <ezLogger/details/logger.hpp>
#include <ezLogger/details/logger_factory.hpp>
#include <ezLogger/sinks/base_sink.hpp>

namespace ezLogger {
namespace sinks {
template <typename Mutex> class stdout_base_sink : public base_sink<Mutex> {
public:
  explicit stdout_base_sink(FILE *file) : base_sink<Mutex>(), _file(file) {}
  ~stdout_base_sink() override = default;
  stdout_base_sink(const stdout_base_sink<Mutex> &bs) = delete;
  stdout_base_sink(stdout_base_sink<Mutex> &&bs) = delete;

  stdout_base_sink &operator=(const stdout_base_sink<Mutex> &bs) = delete;
  stdout_base_sink &operator=(stdout_base_sink<Mutex> &&bs) = delete;

protected:
  void sink_push(const details::log_message &message) override {
    details::dest_t dest;
    base_sink<Mutex>::_formatter->format(message, dest);
    fmt::print(_file, dest);
  }

  virtual std::unique_ptr<stdout_base_sink<Mutex>> _clone() {
    return std::make_unique<stdout_base_sink<Mutex>>(_file);
  }

  std::unique_ptr<base_sink<Mutex>> snk_clone() override { return _clone(); }

  FILE *_file;
};

template <typename Mutex> class stdout_sink : public stdout_base_sink<Mutex> {
protected:
  std::unique_ptr<stdout_base_sink<Mutex>> _clone() override {
    return std::make_unique<stdout_sink<Mutex>>();
  }

public:
  stdout_sink() : stdout_base_sink<Mutex>(stdout) {}
};
template <typename Mutex> class stderr_sink : public stdout_base_sink<Mutex> {
protected:
  std::unique_ptr<stdout_base_sink<Mutex>> _clone() override {
    return std::make_unique<stderr_sink<Mutex>>();
  }

public:
  stderr_sink() : stdout_base_sink<Mutex>(stderr) {}
};

using stdout_sink_mt = stdout_sink<std::mutex>;
using stdout_sink_st = stdout_sink<details::null_mutex>;

using stderr_sink_mt = stderr_sink<std::mutex>;
using stderr_sink_st = stderr_sink<details::null_mutex>;

inline std::shared_ptr<details::logger>
stdout_logger_mt(const std::string &logger_name) {
  return details::logger_factory::create<stdout_sink_mt>(logger_name);
}

inline std::shared_ptr<details::logger>
stdout_logger_st(const std::string &logger_name) {
  return details::logger_factory::create<stdout_sink_st>(logger_name);
}

inline std::shared_ptr<details::logger>
stderr_logger_mt(const std::string &logger_name) {
  return details::logger_factory::create<stderr_sink_mt>(logger_name);
}

inline std::shared_ptr<details::logger>
stderr_logger_st(const std::string &logger_name) {
  return details::logger_factory::create<stderr_sink_st>(logger_name);
}
}; // namespace sinks
}; // namespace ezLogger
