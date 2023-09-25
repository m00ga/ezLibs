#pragma once

#include <cstdio>

#ifndef TEST_LABEL
#define TEST_LABEL "ezLogger"
#endif

#define TEST_CASE_(label, err_message, test_func)                              \
  {                                                                            \
    if (!test_func()) {                                                        \
      std::printf("%s: %s assertion error\n", label, err_message);             \
      return 1;                                                                \
    }                                                                          \
  }

#define TEST_ASSERT(assert)                                                    \
  TEST_CASE_(TEST_LABEL, #assert, [&]() { return assert; })

#define TEST_ASSERTL(label, assert)                                            \
  TEST_CASE_(label, #assert, [&]() { return assert; })

#define TEST_FUNC(func) TEST_CASE_(TEST_LABEL, #func, func)

#define TEST_FUNCL(label, func) TEST_CASE_(label, #func, func)
