#pragma once

#include <cstdint>
#include <memory>
#include <netinet/in.h>
#include <string>

namespace ezNetwork {
namespace ezSocket {
enum class adress_type { INET };

template <adress_type Type> struct adress_data {
  using type = void;

  static std::unique_ptr<type> toNative(const std::string &address,
                                        std::uint16_t port);
  constexpr static std::string_view to_string();
  constexpr static std::uint8_t get_native_enum();
  constexpr static std::uint32_t get_size();
  constexpr static std::string_view
  get_adress(const std::shared_ptr<type> &addr);
  constexpr static std::uint16_t get_port(const std::shared_ptr<type> &addr);
};

template <> struct adress_data<adress_type::INET> {
  using type = sockaddr_in;

  static std::unique_ptr<type> toNative(const std::string &address,
                                        std::uint16_t port);
  constexpr static std::string_view to_string();
  constexpr static std::uint8_t get_native_enum();
  constexpr static std::uint32_t get_size();
  constexpr static std::string_view
  get_adress(const std::shared_ptr<type> &addr);
  constexpr static std::uint16_t get_port(const std::shared_ptr<type> &addr);
};

}; // namespace ezSocket
}; // namespace ezNetwork
