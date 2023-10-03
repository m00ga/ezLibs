#include "./details/logger.hpp"
#include "details/common.hpp"
#include "details/log_level.hpp"
#include "sinks/stdstr_sink.hpp"
#include "test_helper.hpp"
#include <unistd.h>

#include <fmt/core.h>

static const char test_data[] = "test_str";
static char test_file[] = "/tmp/stdstr_test";

int counter = 0;
char buf[64];

int offset = 0;

bool test_level(ezLogger::details::logger &log, FILE *file,
                ezLogger::details::log_level lvl) {
  log.log(lvl, test_data);
  memset(buf, 0, sizeof(buf));
  std::string test_case = fmt::format("{} {} {}", log.name(), test_data,
                                      ezLogger::details::level_to_string(lvl));
  fseek(file, offset, SEEK_SET);
  offset += test_case.length() + 1;
  fread(buf, sizeof(char), test_case.length(), file);
  counter++;

  if (strcmp(buf, test_case.c_str()) == 0) {
    return true;
  } else {
    printf("ezLogger test_level error: expected %s, but got %s\n",
           test_case.c_str(), buf);
    return false;
  }
}

int main() {
  unlink(test_file);
  int tmp = mkstemp(test_file);
  TEST_ASSERT(tmp > 0);

  FILE *file = fdopen(tmp, "w+");
  auto snk = std::make_unique<
      ezLogger::sinks::stdout_base_sink<ezLogger::details::null_mutex>>(file);
  snk->set_pattern("%n %v %l");
  ezLogger::details::logger log("test_logger", std::move(snk));

  unsigned int flag = 0;

  flag |= (1 << (unsigned int)test_level(log, file,
                                         ezLogger::details::log_level::INFO) *
                    counter);
  flag |= (1 << (unsigned int)test_level(log, file,
                                         ezLogger::details::log_level::ERROR) *
                    counter);
  flag |= (1 << (unsigned int)test_level(log, file,
                                         ezLogger::details::log_level::DEBUG) *
                    counter);
  flag |= (1 << (unsigned int)test_level(log, file,
                                         ezLogger::details::log_level::WARN) *
                    counter);
  flag |= (1 << (unsigned int)test_level(log, file,
                                         ezLogger::details::log_level::TRACE) *
                    counter);

  fclose(file);

  if ((flag & ~(0b00011111)) != 0) {
    return 0;
  } else {
    return 1;
  }
}
