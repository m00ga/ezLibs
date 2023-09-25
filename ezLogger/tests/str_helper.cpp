#include "./details/str_hepler.hpp"
#include "./test_helper.hpp"

#include <sstream>
#include <string>
#include <string_view>

#include <climits>

static const std::string_view tst("test");

int main() {
  std::string str_dest;
  std::ostringstream oss_dest;
  ezLogger::details::dest_t dest;

  ezLogger::details::str_helper_<std::string>::append_str(tst, str_dest);
  TEST_ASSERT(str_dest == tst);

  ezLogger::details::str_helper_<std::ostringstream>::append_str(tst, oss_dest);
  TEST_ASSERT(oss_dest.str() == tst);

  ezLogger::details::str_helper::append_str(tst, dest);
  TEST_ASSERT(ezLogger::details::str_helper::get_str(dest) == tst);

  dest.clear();
  ezLogger::details::str_helper::append_str(INT_MAX, dest);
  TEST_ASSERT(ezLogger::details::str_helper::get_str(dest) ==
              std::to_string(INT_MAX))
  return 0;
}
