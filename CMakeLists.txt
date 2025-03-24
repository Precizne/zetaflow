cmake_minimum_required(VERSION 3.20)
project(ZetaFlow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

find_package(Boost REQUIRED COMPONENTS system)

add_executable(zetaflow ${SOURCES})

target_include_directories(zetaflow PRIVATE ${INCLUDE_DIR})
target_link_libraries(zetaflow PRIVATE Boost::system)

target_compile_options(zetaflow PRIVATE -Wall -Wextra -Wpedantic -Werror)
