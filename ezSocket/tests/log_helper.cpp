#include <ezLogger/details/logger.hpp>
#include <ezLogger/sinks/file_sink.hpp>

#include <ezSocket/log_helper.hpp>

#include <fstream>

ezNetwork::ezSocket::log_helper::log_ptr init_logger() {
  std::ofstream file;
  file.open("test_data.txt", std::ios::out | std::ios::trunc);
  file.close();
  auto base = ezLogger::sinks::file_logger_st("base", "test_data.txt");
  return ezNetwork::ezSocket::log_helper::init_logger();
}

int main() {
  auto logger = init_logger();
  ezNetwork::ezSocket::log_helper::log<true>(ezLogger::details::log_level::INFO,
                                       "test_mess {}", "test");
  return 0;
}
