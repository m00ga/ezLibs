#include <ezSocket/adress_data.hpp>

#include <arpa/inet.h>
#include <sys/socket.h>

namespace ezNetwork {
namespace ezSocket {
std::unique_ptr<sockaddr_in>
adress_data<adress_type::INET>::toNative(const std::string &address,
                                         std::uint16_t port) {
  std::unique_ptr<sockaddr_in> hst(new struct sockaddr_in);
  hst->sin_family = AF_INET;
  hst->sin_addr.s_addr = inet_addr(address.c_str());
  hst->sin_port = htons(port);
  return std::move(hst);
}

constexpr std::string_view adress_data<adress_type::INET>::to_string() {
  return "INET";
}

constexpr std::uint8_t adress_data<adress_type::INET>::get_native_enum() {
  return AF_INET;
}

constexpr std::uint32_t adress_data<adress_type::INET>::get_size() {
  return sizeof(sockaddr_in);
}

constexpr std::string_view adress_data<adress_type::INET>::get_adress(
    const std::shared_ptr<sockaddr_in> &addr) {
  return inet_ntoa(addr->sin_addr);
}
constexpr std::uint16_t adress_data<adress_type::INET>::get_port(
    const std::shared_ptr<sockaddr_in> &addr) {
  return htons(addr->sin_port);
}
}; // namespace ezSocket
}; // namespace ezNetwork
