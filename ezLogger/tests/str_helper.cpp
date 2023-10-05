#include "./test_helper.hpp"

#include <climits>
#include <sstream>
#include <string>
#include <string_view>

#include <ezLogger/details/str_hepler.hpp>

static const std::string_view tst("test");

int main() {
  ezLogger::details::dest_t dest;

  ezLogger::details::str_helper::append_str(tst, dest);
  TEST_ASSERT(ezLogger::details::str_helper::get_str(dest) == tst);

  dest.clear();
  ezLogger::details::str_helper::append_str(INT_MAX, dest);
  TEST_ASSERT(ezLogger::details::str_helper::get_str(dest) ==
              std::to_string(INT_MAX))
  return 0;
}
