cmake_minimum_required(VERSION 3.20)
project(ZetaFlow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

option(ENABLE_SANITIZERS "Enable Address, Thread, or Undefined Behavior Sanitizers" OFF)
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)
option(ENABLE_UBSAN "Enable UndefinedBehaviorSanitizer" OFF)

if(ENABLE_SANITIZERS)
    if(ENABLE_ASAN)
        message(STATUS "Enabling AddressSanitizer")
        set(SANITIZER_FLAGS "-fsanitize=address")
    elseif(ENABLE_TSAN)
        message(STATUS "Enabling ThreadSanitizer")
        set(SANITIZER_FLAGS "-fsanitize=thread")
    elseif(ENABLE_UBSAN)
        message(STATUS "Enabling UndefinedBehaviorSanitizer")
        set(SANITIZER_FLAGS "-fsanitize=undefined")
    else()
        message(WARNING "ENABLE_SANITIZERS is ON, but no specific sanitizer is selected.")
    endif()

    if(SANITIZER_FLAGS)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS} -fno-omit-frame-pointer")
    endif()
endif()

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
