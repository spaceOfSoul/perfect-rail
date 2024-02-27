cmake_minimum_required(VERSION 3.10)
project(PerfectRail)

set(CMAKE_CXX_STANDARD 17)

#최적화 비활성화
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

#릴리즈 모드(최적화 활성화)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCES "*.cpp")
add_executable(PerfectRail ${SOURCES})
target_link_libraries(PerfectRail sfml-graphics sfml-audio)

file(COPY ${CMAKE_SOURCE_DIR}/bgm DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/fonts DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Songs DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/Sounds DESTINATION ${CMAKE_BINARY_DIR})
