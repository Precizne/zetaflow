cmake_minimum_required(VERSION 3.20)
project(ZetaFlow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)

include_directories(${INCLUDE_DIR} ${GEN_DIR})

find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenSSL REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

file(GLOB PROTO_SRCS ${GEN_DIR}/*.pb.cc ${GEN_DIR}/*.grpc.pb.cc)

add_executable(zetaflow ${SOURCES} ${PROTO_SRCS})

target_include_directories(zetaflow PRIVATE ${INCLUDE_DIR} ${GEN_DIR})

target_link_libraries(zetaflow PRIVATE 
    Boost::system
    gRPC::grpc++
    OpenSSL::SSL
    OpenSSL::Crypto
    protobuf::libprotobuf
    Threads::Threads
)

target_compile_options(zetaflow PRIVATE -Wall -Wextra -Wpedantic -Werror)
