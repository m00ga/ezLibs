#include <memory>

#include <ezLogger/details/logger.hpp>
#include <ezLogger/details/logger_factory.hpp>
#include <ezLogger/ezLogger.hpp>
#include <ezLogger/sinks/file_sink.hpp>
#include <ezLogger/sinks/stdstr_sink.hpp>

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
  init_logger("tester");

  ezLogger::get("tester")->info("info message");
  ezLogger::get("tester")->error("we have problems");

  return 0;
}
