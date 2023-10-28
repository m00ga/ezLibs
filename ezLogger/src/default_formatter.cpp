#include <ezLogger/default_formatter.hpp>
#include <ezLogger/details/str_hepler.hpp>
#include <ezLogger/format_flags.hpp>

#define HANDLE_FLAG(ch, name, dest)                                            \
  case ch: {                                                                   \
    dest.push_back(std::make_unique<name>());                                  \
    break;                                                                     \
  };

namespace ezLogger {
void default_formatter::handleFlag(char flag) {
  auto it = _customFlags.find(flag);
  if (it != _customFlags.end()) {
    auto data = it->second->clone();
    _flags.push_back(std::move(data));
    return;
  }

  switch (flag) {
    HANDLE_FLAG('v', flags::payload_flag, _flags);
    HANDLE_FLAG('l', flags::level_flag, _flags);
    HANDLE_FLAG('n', flags::name_flag, _flags);
    HANDLE_FLAG('Y', flags::Y_flag, _flags);
    HANDLE_FLAG('m', flags::m_flag, _flags);
    HANDLE_FLAG('d', flags::d_flag, _flags);
    HANDLE_FLAG('H', flags::H_flag, _flags);
    HANDLE_FLAG('M', flags::M_flag, _flags);
    HANDLE_FLAG('S', flags::S_flag, _flags);
    HANDLE_FLAG('+', flags::default_flag, _flags);
  }
}

void default_formatter::compile_pattern(std::string_view pattern) {
  auto end = pattern.end();
  _flags.clear();
  std::unique_ptr<flags::aggregate_flag> user_chars;
  for (auto it = pattern.begin(); it != end; ++it) {
    if (*it == '%') {
      if (user_chars) {
        _flags.push_back(std::move(user_chars));
      }
      if (it + 1 != end) {
        ++it;
        handleFlag(*it);
      } else {
        break;
      }
    } else {
      if (!user_chars) {
        user_chars = std::make_unique<flags::aggregate_flag>();
      }

      user_chars->add_ch(*it);
    }
  }
  if (user_chars) {
    _flags.push_back(std::move(user_chars));
  }
}

default_formatter::default_formatter() {
  _pattern = "%+";
  _flags.push_back(std::make_unique<flags::default_flag>());
}

default_formatter::default_formatter(const std::string &pattern) {
  _pattern = pattern;
  compile_pattern(_pattern);
}

default_formatter::default_formatter(std::string &&pattern) {
  _pattern = std::move(pattern);
  compile_pattern(_pattern);
}

void default_formatter::set_custom_flags(custom_flags_map &&flags) {
  _customFlags.clear();
  _customFlags = std::move(flags);
}

void default_formatter::add_custom_flag(
    char flag, std::unique_ptr<details::custom_flag> &&custom_flag) {
  _customFlags.insert({flag, std::move(custom_flag)});
}
void default_formatter::set_pattern(const std::string &pattern) {
  _pattern = pattern;
  compile_pattern(_pattern);
}

void default_formatter::format(const details::log_message &msg,
                               details::dest_t &dest) {
  for (auto &fmt : _flags) {
    fmt->format(msg, dest);
  }
  details::str_helper::append_eol(dest);
}
std::unique_ptr<details::formatter> default_formatter::clone() {
  custom_flags_map flags;
  for (auto &flg : _customFlags) {
    flags[flg.first] = flg.second->clone();
  }
  auto cloned = std::make_unique<default_formatter>(_pattern);
  cloned->set_custom_flags(std::move(flags));
  return cloned;
}
const std::string default_formatter::pattern() const { return _pattern; }

}; // namespace ezLogger
