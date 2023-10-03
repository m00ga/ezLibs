#include "./details/common.hpp"
#include "./details/logger_factory.hpp"
#include "./sinks/stdstr_sink.hpp"
#include "./test_helper.hpp"
#include "details/log_message.hpp"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

static const char test_data[] = "test test_str INFO";
static char test_file[] = "/tmp/stdstr_test";

int main() {
  unlink(test_file);
  int tmp = mkstemp(test_file);
  TEST_ASSERT(tmp > 0);

  FILE *file = fdopen(tmp, "w+");
  auto snk = ezLogger::details::sink_factory::create<
      ezLogger::sinks::stdout_base_sink<ezLogger::details::null_mutex>>(file);
  snk->set_pattern("%n %v %l");

  ezLogger::details::log_message msg("test", "test_str",
                                     ezLogger::details::log_level::INFO);
  snk->log(msg);
  fseek(file, 0, SEEK_SET);

  char buf[256];
  fread(buf, sizeof(char), sizeof(test_data), file);
  buf[sizeof(test_data) - 1] = '\0';
  fclose(file);

  TEST_ASSERT(strcmp(test_data, buf) == 0);
}
