cmake_minimum_required(VERSION 3.21.1)

project(TradingSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "bin")

include_directories("./include")

if (UNIX)
  string(APPEND CMAKE_CXX_FLAGS " -Wall -Werror -Wno-format-security -Wno-self-assign-overloaded")
endif()

add_executable(TradingSimulator 
	src/main.cpp)



