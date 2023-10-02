#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>

namespace ezLogger {
namespace details {
class log_context {
private:
  std::unordered_map<std::string, std::shared_ptr<void>> _ctx_map;

public:
  ~log_context() { _ctx_map.clear(); }

  template <typename T, typename... Args>
  void add(const std::string &key, Args &&...args) {
    _ctx_map[key] = std::make_shared<T>(std::forward<Args>(args)...);
  }

  template <typename T> std::shared_ptr<T> get(const std::string &key) {
    auto it = _ctx_map.find(key);
    return it != _ctx_map.end() ? std::static_pointer_cast<T>(it->second)
                                : nullptr;
  }

  void remove(const std::string &key) {
    auto it = _ctx_map.find(key);
    if (it != _ctx_map.end()) {
      it->second.reset();
      _ctx_map.erase(it);
    }
  }
};
}; // namespace details
}; // namespace ezLogger
