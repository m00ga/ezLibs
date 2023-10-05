#include <ezLogger/details/str_hepler.hpp>

namespace ezLogger {
namespace details {

void str_helper::append_str(std::string_view str, dest_t &dest) {
  dest.append(str);
}

std::string str_helper::get_str(const dest_t &dest) { return dest; }

void str_helper::append_eol(dest_t &dest) { dest += "\n"; }
}; // namespace details
}; // namespace ezLogger
