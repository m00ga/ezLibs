#include "./details/str_hepler.hpp"

#include <sstream>
#include <string>
#include <string_view>

static const std::string_view tst("test");

int main() {
  std::string str_dest;
  std::ostringstream oss_dest;
  ezLogger::details::dest_t dest;

  ezLogger::details::str_helper_<std::string>::append_str(tst, str_dest);
  if (str_dest != tst)
    return 1;
  ezLogger::details::str_helper_<std::ostringstream>::append_str(tst, oss_dest);
  if (oss_dest.str() != tst)
    return 1;
  ezLogger::details::str_helper::append_str(tst, dest);
  if (ezLogger::details::str_helper::get_str(dest) != tst)
    return 1;
  return 0;
}
