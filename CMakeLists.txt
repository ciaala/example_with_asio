cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ASIO_EXAMPLE)
set(CMAKE_CXX_FLAGS -DASIO_STANDALONE)
SET(SOURCE_FILES code/echo.cpp code/connection.h)

add_executable(echo-server ${SOURCE_FILES})
target_include_directories(echo-server PUBLIC asio-1.10.6/include)

add_executable(check-the-move code/check-the-move.cpp)
