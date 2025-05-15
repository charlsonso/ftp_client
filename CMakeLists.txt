cmake_minimum_required(VERSION 3.10)

project(ftp_client VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include(FetchContent)

FetchContent_Declare(
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse
)

FetchContent_MakeAvailable(argparse)

add_executable(ftp_client src/main.cpp)
target_link_libraries(ftp_client argparse)
