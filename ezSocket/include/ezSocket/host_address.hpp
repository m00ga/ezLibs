#pragma once

#include <cstdint>
#include <ezSocket/address_data.hpp>
#include <ezSocket/log_helper.hpp>

#include <memory>
#include <string>
#include <utility>

namespace ezNetwork {
namespace ezSocket {
template <address_type T, typename R = typename address_data<T>::type>
class host_address {
private:
  std::unique_ptr<R> _native_addr;
  std::string _address;
  std::uint16_t _port;

public:
  host_address() : _native_addr(nullptr), _port(0), _address() {
    log_helper::log(ezLogger::details::log_level::INFO,
                    "Created new host_address of {} type without address and "
                    "port with {} ptr",
                    -1, addr_type_to_string(T), fmt::ptr(this));
  }
  host_address(const std::string &address, std::uint16_t port) {
    _address = address;
    _port = port;
    _native_addr = std::move(address_data<T>::toNative(_address, _port));
    log_helper::log(ezLogger::details::log_level::INFO,
                    "Created new host_address of {} type with {} ptr {} "
                    "address and {} port",
                    -1, addr_type_to_string(T), fmt::ptr(this), _address,
                    _port);
  }
  host_address(host_address<T, R> &&address) {
    _native_addr = std::move(address._native_addr);
    _address = address._address;
    _port = address._port;
    log_helper::log(
        ezLogger::details::log_level::INFO,
        "Created new host_address of {} type with {} ptr {} "
        "address and {} port from other host_address with {} type and {} ptr",
        -1, addr_type_to_string(T), fmt::ptr(this), _address, _port,
        addr_type_to_string(T), fmt::ptr(&address));
  }
  host_address(const host_address<T, R> &other) = delete;

  ~host_address() = default;

  void set_addr(std::unique_ptr<R> &&addr) {
    _native_addr = std::move(addr);
    _address = address_data<T>::get_address(_native_addr);
    _port = address_data<T>::get_port(_native_addr);
    log_helper::log(ezLogger::details::log_level::DEBUG,
                    "Moved unique_ptr with {} address and {} port into "
                    "host_adress with {} ptr and {} type",
                    -1, _address, _port, fmt::ptr(this),
                    addr_type_to_string(T));
  }
  void set_addr(const std::string &address, std::uint16_t port) {
    _address = address;
    _port = port;
    _native_addr = std::move(address_data<T>::toNative(_address, _port));
    log_helper::log(
        ezLogger::details::log_level::DEBUG,
        "Set {} address and {} port to host_adress with {} ptr and {} type", -1,
        _address, _port, fmt::ptr(this), addr_type_to_string(T));
  }

  std::string get_address() const { return _address; }
  std::uint16_t get_port() const { return _port; }
  const R *get_native() const { return _native_addr.get(); }

  host_address<T, R> clone() {
    return std::move(host_address<T, R>(_address, _port));
  }

  host_address<T, R> &operator=(host_address<T, R> &&other) {
    this->_native_addr = std::move(other._native_addr);
    _address = other._address;
    _port = other._port;
    log_helper::log(ezLogger::details::log_level::DEBUG,
                    "host_adress with {} type and {} ptr assigned to "
                    "host_address with {} ptr",
                    -1, addr_type_to_string(T), fmt::ptr(&other),
                    fmt::ptr(this));

    return *this;
  }
};
}; // namespace ezSocket
}; // namespace ezNetwork
