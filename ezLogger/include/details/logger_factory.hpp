#pragma once

#include "./registry.hpp"
#include "details/logger.hpp"
#include "details/sink.hpp"
#include <memory>
#include <string>
#include <type_traits>
#include <utility>
namespace ezLogger {
namespace details {
class sink_factory {
public:
  template <typename Sink, typename... Args,
            std::enable_if_t<std::is_base_of_v<sink, Sink>, bool> = true>
  inline static std::unique_ptr<Sink> create(Args &&...args) {
    return std::make_unique<Sink>(std::forward<Args>(args)...);
  }
};

class logger_factory {
public:
  template <typename Sink, typename... Args,
            std::enable_if_t<std::is_base_of_v<sink, Sink>, bool> = true>
  inline static std::shared_ptr<logger> create(const std::string &name,
                                               Args &&...args) {
    auto sink = sink_factory::create<Sink>(std::forward<Args>(args)...);
    auto log = std::make_shared<logger>(name, std::move(sink));
    registry::instance().initalize_logger(log);
    return log;
  }
};
}; // namespace details
}; // namespace ezLogger
