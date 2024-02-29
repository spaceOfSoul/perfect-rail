cmake_minimum_required(VERSION 3.10)
project(SFMLTest)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCES "*.cpp")

add_executable(SFMLTest ${SOURCES})

target_link_libraries(SFMLTest sfml-graphics sfml-audio)

file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Sounds DESTINATION ${CMAKE_BINARY_DIR})
