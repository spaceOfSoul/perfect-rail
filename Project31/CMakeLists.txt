cmake_minimum_required(VERSION 3.10)
project(PerfectRail)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(PerfectRail main.cpp)
target_link_libraries(PerfectRail sfml-graphics sfml-audio)
