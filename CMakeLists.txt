cmake_minimum_required(VERSION 3.21.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(main)

set(EXECUTABLE_OUTPUT_PATH "bin")

find_package(wxWidgets REQUIRED COMPONENTS net core base)

if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

# add src files
file(GLOB_RECURSE SRC_FILES src/*.cpp)

#add header files
include_directories(
   "./include"
	${SFML_INCLUDE_DIRS} 
)

if (UNIX)
  string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wno-format-security -Wno-self-assign-overloaded")
endif()

add_executable(main 
	${SRC_FILES}
)
target_link_libraries(main ${wxWidgets_LIBRARIES})
