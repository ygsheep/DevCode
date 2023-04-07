cmake_minimum_required(VERSION 3.0.0)
project(yazi VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include/)

file(GLOB_RECURSE SRC_FILES src/*.cpp)

add_executable(yazi
  main.cpp
  ${SRC_FILES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 11)
include(CPack)

add_custom_target(
  TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/assets
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/assets/test.json ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug
)