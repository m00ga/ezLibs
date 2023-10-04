#pragma once

#include <cstdio>
#include <filesystem>
#include <memory>
#include <string>

#include "./details/logger_factory.hpp"
#include "details/common.hpp"
#include "details/logger.hpp"
#include "sinks/base_sink.hpp"
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

public:
  explicit file_sink(const std::filesystem::path &path) {
    _file = fopen(path.c_str(), "w");
    if (_file == nullptr) {
      throw std::runtime_error("file_sink creation error");
    }
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
