#include "./details/str_hepler.hpp"

namespace ezLogger {
namespace details {
void str_helper_<std::string>::append_str(std::string_view str,
                                          std::string &dest) {
  dest.append(str);
}

std::string str_helper_<std::string>::get_str(const std::string &dest) {
  return dest;
}

void str_helper_<std::ostringstream>::append_str(std::string_view str,
                                                 std::ostringstream &dest) {
  dest << str;
}

std::string
str_helper_<std::ostringstream>::get_str(const std::ostringstream &dest) {
  return dest.str();
}

void str_helper::append_str(std::string_view str, dest_t &dest) {
  str_helper_<dest_t>::append_str(str, dest);
}

std::string str_helper::get_str(const dest_t &dest) {
  return str_helper_<dest_t>::get_str(dest);
}
}; // namespace details
}; // namespace ezLogger
