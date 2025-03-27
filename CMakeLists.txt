cmake_minimum_required(VERSION 3.20)
project(ZetaFlow VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(GEN_DIR ${CMAKE_SOURCE_DIR}/generated)
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)

file(MAKE_DIRECTORY ${GEN_DIR})

find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

include_directories(${INCLUDE_DIR} ${GEN_DIR})

file(GLOB_RECURSE PROTO_FILES ${PROTO_DIR}/*.proto)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_FILES})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_FILES})

add_custom_target(copy_proto_files ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory ${GENERATED_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROTO_SRCS} ${GENERATED_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROTO_HDRS} ${GENERATED_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GRPC_SRCS} ${GENERATED_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${GRPC_HDRS} ${GENERATED_DIR}
    COMMENT "Copying generated protobuf and gRPC files to ${GENERATED_DIR}"
)

file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

add_executable(zetaflow ${SOURCES} ${PROTO_SRCS} ${GRPC_SRCS})

target_include_directories(zetaflow PRIVATE ${INCLUDE_DIR} ${PROTO_HDRS} ${GRPC_HDRS})

target_link_libraries(zetaflow PRIVATE 
    Boost::system
    gRPC::grpc++
    OpenSSL::SSL
    OpenSSL::Crypto
    protobuf::libprotobuf
    pthread
)

target_compile_options(zetaflow PRIVATE -Wall -Wextra -Wpedantic -Werror)
