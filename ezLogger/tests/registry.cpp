#include "./registry.hpp"
#include "./details/logger_factory.hpp"
#include "./sinks/stdstr_sink.hpp"
#include "details/common.hpp"
#include "test_helper.hpp"
#include <unistd.h>

const char test_data[] = "test test_str";
const char test1_data[] = "test1 test_str";
char test_file[] = "/tmp/registry-test";

int main() {
  ezLogger::registry::instance().set_pattern("%n %v");
  unlink(test_file);
  int tmp = mkstemp(test_file);
  TEST_ASSERT(tmp > 0);

  FILE *file = fdopen(tmp, "w+");
  auto log = ezLogger::details::logger_factory::create<
      ezLogger::sinks::stdout_base_sink<ezLogger::details::null_mutex>>("test",
                                                                        file);

  ezLogger::registry::instance().set_default_logger(std::move(log));

  ezLogger::registry::instance().default_logger()->info("test_str");

  fseek(file, 0, SEEK_SET);
  char buf[64];
  fread(buf, sizeof(char), sizeof(test_data), file);
  buf[sizeof(test_data) - 1] = '\0';

  TEST_ASSERT(strcmp(test_data, buf) == 0);

  fseek(file, 0, SEEK_SET);

  auto tst = ezLogger::details::logger_factory::create<
      ezLogger::sinks::stdout_base_sink<ezLogger::details::null_mutex>>("test1",
                                                                        file);

  auto logger = ezLogger::registry::instance().get("test1");
  TEST_ASSERT(logger != nullptr);
  logger->info("test_str");
  fseek(file, 0, SEEK_SET);
  memset(buf, 0, sizeof(buf));
  fread(buf, sizeof(char), sizeof(test1_data), file);
  buf[sizeof(test1_data) - 1] = '\0';
  fclose(file);

  TEST_ASSERT(strcmp(test1_data, buf) == 0);
}
