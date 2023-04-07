cmake_minimum_required(VERSION 3.25)

# set(CMAKE_CURRENT_SOURCE_DIR "~/workspace")
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
#   CACHE STRING "Vcpkg toolchain file")

find_package(OpenCV REQUIRED)
project(main )

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME} 
	main.cpp
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
