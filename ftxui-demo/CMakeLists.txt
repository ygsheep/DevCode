cmake_minimum_required(VERSION 3.2.0)
# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(Example)



file(GLOB SRC_FILES
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	)

# add_library(main STATIC ${SRC_FILES})
# add the executable
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})


find_package(fmt CONFIG REQUIRED)
find_package(ftxui CONFIG REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE ftxui::dom ftxui::screen ftxui::component)


