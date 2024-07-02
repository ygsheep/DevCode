# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name
project(CPPTest)



file(GLOB INCLUDE_FILES
	"${PROJECT_SOURCE_DIR}/include/*.h"
	"${PROJECT_SOURCE_DIR}/include/*.hpp"
	)

file(GLOB SRC_FILES 
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.c"
)

# add_library(main STATIC ${SRC_FILES})
# add the executable
add_executable(${CMAKE_PROJECT_NAME} 
	${SRC_FILES} 
	"src/Ä¬ÈÏÊµ²Î.cpp"

)

