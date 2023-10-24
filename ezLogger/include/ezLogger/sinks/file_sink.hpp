#pragma once

#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>

#include <ezLogger/details/common.hpp>
#include <ezLogger/details/logger.hpp>
#include <ezLogger/details/logger_factory.hpp>
#include <ezLogger/sinks/base_sink.hpp>
namespace ezLogger {
namespace sinks {
template <typename Mutex> class file_sink : public base_sink<Mutex> {
private:
  FILE *_file;

  void sink_push(const details::log_message &msg) override {
    details::dest_t dest;
    base_sink<Mutex>::_formatter->format(msg, dest);
    fmt::print(_file, dest);
  }
  std::unique_ptr<base_sink<Mutex>> snk_clone() override {
    return std::make_unique<file_sink<Mutex>>(_file);
  }

public:
  explicit file_sink(const std::filesystem::path &path) {
    _file = fopen(path.c_str(), "w");
    if (_file == nullptr) {
      throw std::runtime_error("file_sink creation error");
    }
  }

  explicit file_sink(FILE *file) {
    if (_file == nullptr) {
      throw std::runtime_error("file_sink creation error");
    }
    _file = file;
  }

  file_sink(const file_sink<Mutex> &bs) = delete;
  file_sink(file_sink<Mutex> &&bs) = delete;

  file_sink &operator=(const file_sink<Mutex> &bs) = delete;
  file_sink &operator=(file_sink<Mutex> &&bs) = delete;

  ~file_sink() { fclose(_file); }
};

using file_sink_st = file_sink<details::null_mutex>;
using file_sink_mt = file_sink<std::mutex>;

inline std::shared_ptr<details::logger>
file_logger_mt(const std::string &logger_name,
               const std::filesystem::path &file_path) {
  return details::logger_factory::create<file_sink_mt>(logger_name, file_path);
}
inline std::shared_ptr<details::logger>
file_logger_st(const std::string &logger_name,
               const std::filesystem::path &file_path) {
  return details::logger_factory::create<file_sink_st>(logger_name, file_path);
}

}; // namespace sinks
}; // namespace ezLogger
