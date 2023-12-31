set(COMPONENT_NAME ezLogger)
set(COMPONENT_SOURCES src/str_helper.cpp src/format_flags.cpp
                      src/default_formatter.cpp src/logger.cpp src/registry.cpp)
set(COMPONENT_VERSION 1.0.0)
set(COMPONENT_SOVERSION 1)

find_package(fmt REQUIRED)

add_library(${COMPONENT_NAME} SHARED ${COMPONENT_SOURCES})
add_library(${ROOT_PROJECT}::${COMPONENT_NAME} ALIAS ${COMPONENT_NAME})

set_target_properties(
  ${COMPONENT_NAME}
  PROPERTIES VERSION ${COMPONENT_VERSION}
             SOVERSION ${COMPONENT_SOVERSION}
             DEBUG_POSTFIX "d")

target_include_directories(
  ${COMPONENT_NAME}
  PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
         $<INSTALL_INTERFACE:include/${ROOT_PROJECT}>)

target_compile_features(${COMPONENT_NAME} PUBLIC cxx_std_17)
target_link_libraries(${COMPONENT_NAME} PUBLIC fmt::fmt)

if(DEFINED EZLOGGER_BUILD_TESTS)
  add_subdirectory(tests)
endif()

install(
  TARGETS ${COMPONENT_NAME}
  EXPORT ${COMPONENT_NAME}-targets
  COMPONENT ${COMPONENT_NAME}
  ARCHIVE DESTINATION lib/${ROOT_PROJECT}
  LIBRARY DESTINATION lib/${ROOT_PROJECT})
install(
  EXPORT ${COMPONENT_NAME}-targets
  FILE "${ROOT_PROJECT}-${COMPONENT_NAME}-targets.cmake"
  NAMESPACE ${ROOT_PROJECT}::
  DESTINATION lib/cmake/${ROOT_PROJECT}
  COMPONENT ${COMPONENT_NAME})

configure_file(
  "${COMPONENT_NAME}-config.cmake.in"
  "${CMAKE_BINARY_DIR}/${ROOT_PROJECT}-${COMPONENT_NAME}-config.cmake" @ONLY)

install(
  FILES "${CMAKE_BINARY_DIR}/${ROOT_PROJECT}-${COMPONENT_NAME}-config.cmake"
  DESTINATION lib/cmake/${ROOT_PROJECT}
  COMPONENT ${COMPONENT_NAME})

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/${COMPONENT_NAME}/
        DESTINATION include/${ROOT_PROJECT}/${COMPONENT_NAME})
