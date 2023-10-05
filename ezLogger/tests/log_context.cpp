#include "./test_helper.hpp"

#include <cstring>

#include <ezLogger/details/log_context.hpp>

struct test {
  int a;
  char tst[16];
  explicit test(int t) : a(t), tst("test_str") {}
};

int main() {
  ezLogger::details::log_context ctx;
  ctx.add<test>("test_obj", 12);

  TEST_ASSERT(ctx.get<test>("test") == nullptr);
  auto ctx_out = ctx.get<test>("test_obj");

  TEST_ASSERT(ctx_out != nullptr);
  TEST_ASSERT(ctx_out->a == 12 && (strcmp(ctx_out->tst, "test_str") == 0));
}
