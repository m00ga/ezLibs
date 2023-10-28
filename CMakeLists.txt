cmake_minimum_required(VERSION 3.9)

set(ROOT_PROJECT ezLibs)
set(ROOT_VERSION 1.0.0)

project(
  ${ROOT_PROJECT}
  LANGUAGES CXX
  VERSION ${ROOT_VERSION})

add_subdirectory(ezTest)
add_subdirectory(ezLogger)
add_subdirectory(ezSocket)

configure_file(${ROOT_PROJECT}Config.cmake
               "${CMAKE_BINARY_DIR}/${ROOT_PROJECT}Config.cmake" @ONLY)

install(FILES "${CMAKE_BINARY_DIR}/${ROOT_PROJECT}Config.cmake"
        DESTINATION lib/cmake/${ROOT_PROJECT})
