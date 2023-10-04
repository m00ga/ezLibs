#include "./ezLogger.hpp"
#include "./details/logger.hpp"
#include "details/logger_factory.hpp"
#include "sinks/file_sink.hpp"
#include "sinks/stdstr_sink.hpp"

#include <memory>

void init_logger(const std::string &name) {
  auto stout = ezLogger::details::sink_factory::create<
      ezLogger::sinks::stdout_sink_st>();
  stout->should_log(ezLogger::details::log_level::INFO);
  auto f_snk =
      ezLogger::details::sink_factory::create<ezLogger::sinks::file_sink_st>(
          "errorlog.txt");
  f_snk->should_log(ezLogger::details::log_level::ERROR);

  auto log = std::make_shared<ezLogger::details::logger>(name, std::move(stout),
                                                         std::move(f_snk));

  ezLogger::registry::instance().initalize_logger(log);
}

int main() {
  init_logger("zheka");

  ezLogger::get("zheka")->info("info message");
  ezLogger::get("zheka")->error("we have problems");

  return 0;
}
