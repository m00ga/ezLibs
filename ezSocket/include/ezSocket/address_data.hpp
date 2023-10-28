#pragma once

#include <cstdint>
#include <memory>
#include <netinet/in.h>
#include <string>

namespace ezNetwork {
namespace ezSocket {
enum class address_type { INET };

constexpr std::string_view addr_type_to_string(address_type addr_type) {
  switch (addr_type) {
  case address_type::INET:
    return "INET";
  }
}

template <address_type Type> struct address_data {
  using type = void;

  static std::unique_ptr<type> toNative(const std::string &address,
                                        std::uint16_t port);
  constexpr static std::uint8_t get_native_enum();
  constexpr static std::uint32_t get_size();
  constexpr static std::string_view
  get_address(const std::shared_ptr<type> &addr);
  constexpr static std::uint16_t get_port(const std::shared_ptr<type> &addr);
};

template <> struct address_data<address_type::INET> {
  using type = sockaddr_in;

  static std::unique_ptr<type> toNative(const std::string &address,
                                        std::uint16_t port);
  constexpr static std::uint8_t get_native_enum();
  constexpr static std::uint32_t get_size();
  constexpr static std::string_view
  get_address(const std::shared_ptr<type> &addr);
  constexpr static std::uint16_t get_port(const std::shared_ptr<type> &addr);
};

}; // namespace ezSocket
}; // namespace ezNetwork
