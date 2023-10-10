cmake_minimum_required(VERSION 3.2.0)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Example)



file(GLOB SRC_FILES
	"${PROJECT_SOURCE_DIR}/*.cpp"
	"${PROJECT_SOURCE_DIR}/*.c"
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	)

# add_library(main STATIC ${SRC_FILES})
# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})


find_package(fmt CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt)



add_custom_target(
  TARGET ${CMAKE_PROJECT_NAME}
  POST_BUILD
  # COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_SOURCE_DIR}/build/Debug/assets
	COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/build_Debug/${CMAKE_PROJECT_NAME} ${PROJECT_SOURCE_DIR}

)
